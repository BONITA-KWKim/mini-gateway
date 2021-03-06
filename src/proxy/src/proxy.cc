#include "proxy.hh"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

int get_options (int argc, char *argv[]) 
{
    int c = -1;
	while (-1 != (c = getopt (argc, argv, "hl:"))) {
		switch(c) {
		case 'h':		// Show Help message
			show_help ();
			return 1;
		case 'l': // Log Level
			gLoglevel = strtol (optarg, NULL, 16);	// Hex string to long
			break;
        default:
            break;
		}
	}

    return 0;
}

void show_help (void) 
{
	fprintf (stdout, "proxy [-h] [-l log_level] \r\n");
	fprintf (stdout, "    -h: Show help\n");
	fprintf (stdout, "    -l: Log level (hex string)\n");
}

int get_config(char * config_file) 
{
    // std::ifstream is RAII, i.e. no need to call close
    std::cout << COUT_PREFIX << "parse config" << std::endl;

    std::ifstream cFile (config_file);
    if (cFile.is_open ()) {
        std::string line;
        while (getline (cFile, line)) {
            if(line[0] == '#' || line.empty())
                continue;

            // get key-value pair
            auto delimiterPos = line.find ("=");
            std::string key = line.substr( 0, delimiterPos);
            std::string value = line.substr (delimiterPos + 1);
            // insert map
            proxy_env[key]= value;
        }
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }
    return 0;
}

int init_socket (int port_no) 
{
    int server_fd; 
    int opt = 1;
    struct sockaddr_in proxy_address;
    // Creating socket file descriptor 
    if ((server_fd = socket (AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror ("socket failed"); 
        exit (EXIT_FAILURE); 
    }

	if (0 > setsockopt (server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
        sizeof(opt))) { 
		perror ("setsockopt"); 
		exit (EXIT_FAILURE); 
	} 

    proxy_address.sin_family      = AF_INET; 
    proxy_address.sin_addr.s_addr = INADDR_ANY;
    proxy_address.sin_port        = htons (port_no); 

    if (0 > bind (server_fd, (struct sockaddr *)&proxy_address, 
        sizeof (proxy_address))) { 
        perror ("bind failed"); 
        exit (EXIT_FAILURE); 
    } 
    if (0 > listen (server_fd, 3)) { 
        perror ("listen"); 
        exit (EXIT_FAILURE); 
    } 
 
    return server_fd;
}

int event_select (int sockfd, int timeoutSec, int timeoutMSec)
{
	struct timeval timeout;
	fd_set         fdset;
	int            rc, so_error;
	socklen_t 	   len;

	timeout.tv_sec  = timeoutSec;   /* Seconds */
	timeout.tv_usec = timeoutMSec;  /* micro Seconds */
	FD_ZERO(&fdset);
	FD_SET (sockfd, &fdset);

	rc = select (sockfd + 1, &fdset, (fd_set *)0, (fd_set *)0, (struct timeval *)&timeout);
	if (rc > 0) {
		// Event occurred
		if (FD_ISSET (sockfd, &fdset)) {
			so_error = -1;
			len      = sizeof (so_error);
			getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
			
            if (so_error == 0)	return rc;
		}
	} else {
		// Timeout
	}
	return rc;
}

int api_call_atalk (char *buffer) 
{
	http_client client (U("http://localhost:34568/"));
    uri_builder builder (U("/v1/IMS/"));
    builder.append_path (U("kakao-atalk"));

    json::value json_telegram;
    json_telegram[U("message")] = json::value::string (U(buffer));

    http_request req(methods::POST);
    req.set_request_uri(builder.to_string());
    req.set_body(json_telegram);

    try{
        client.request (req).then([=](http_response response) {
            ucout << COUT_PREFIX << U("STATUS : ") << response.status_code() << std::endl;
            ucout << COUT_PREFIX << U("content-type : ") << response.headers().content_type() << std::endl;

            if (200 != response.status_code()) {
                // Error
            }
        }).wait();
    } catch (const std::exception &e) {
        //printf("[%s:%d]Error exception:%s\n", __func__, __LINE__, e.what());
        std::cout << COUT_PREFIX << "Error exception: " << e.what() << std::endl;
    }   
}

void *packet_handler (void *arg)
{
    int sockfd = *(int *)arg;

    int bytecount;
    char buffer[MAX_PACKET_BUFF_SIZE];

    int rc = 0;
    std::string parsed_str;
    while (true) {
        if (1 > (rc = event_select (sockfd, 1, 0))) {
            /* no event */
            continue;
        }

        /* receive socket data */
        bytecount = 0;
        memset (buffer, 0, MAX_PACKET_BUFF_SIZE);
        rc = recv (sockfd, buffer, MAX_PACKET_BUFF_SIZE, 0);

        if (0 > rc) {
            // peer client is killed
            fprintf (stderr, "Client is killed(0 > recv()): %d\n", errno);
            break;
        }

        if (0 == rc) {
            // peer client is killed
            fprintf (stderr, "Client is killed(0 == recv()): %d\n", errno);
            break;
        }

        //printf ("[%s:%d]rc: %d\n", __func__, __LINE__, rc);
        std::cout << COUT_PREFIX << "rc: " << rc << std::endl;
        //printf ("[%s:%d]Received string \"%s\"\n", __func__, __LINE__, buffer);
        //std::cout << "[" << __func__ << ":" <<  __LINE__ <<  "]" << "Received string: " << buffer << std::endl;
        std::cout << COUT_PREFIX << "Received string: " << buffer << std::endl;

        /* find EOP */
		const char eop_pattern[] = "END";
        int end_position = strlen (buffer) - strlen( eop_pattern);
        std::cout << COUT_PREFIX << "string length: " << strlen(buffer) <<
            ", eop pattern length: " << sizeof eop_pattern << ", end_pos: " << end_position << std::endl;
        if (0 != strncmp(&buffer[end_position], eop_pattern, sizeof eop_pattern)) {
            // not found EOP
            std::cout << COUT_PREFIX << "EOP is not found." << std::endl;

            memset (buffer, 0, MAX_PACKET_BUFF_SIZE);
            strcat(buffer, " EOP not found");
        } else {
            /* API call */
            api_call_atalk (buffer);

            memset (buffer, 0, MAX_PACKET_BUFF_SIZE);
            strcat(buffer, " SERVER ECHO");
        }

        std::cout << COUT_PREFIX << "ack bytes: " << bytecount 
            << ", Received string: " << buffer << std::endl;

        /* ACK */
        if((bytecount = send(sockfd, buffer, strlen(buffer), 0))== -1){
            fprintf(stderr, "Error sending data %d\n", errno);
        }

        std::cout << COUT_PREFIX << "Sent bytes: " << bytecount << std::endl;
    }
}

int main (int argc, char *argv[]) 
{
    /* init */
    /* get options when starting program */
    int result = get_options (argc, argv);
    if (1 == result) {
        // show help
        return 0;
    } else if (0 > result) {
        return -1;
    } 

    /// get configuration
    /// check env value
    get_config ("../config/proxy.conf");
    for (auto it = proxy_env.cbegin(); it != proxy_env.cend(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    /// socket
    ///
    int new_socket = -1;
    int master_socket = -1;
    master_socket = init_socket(8520);
    if (0 > master_socket) {
        perror ("master socket");
        exit(1);
    }

    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    //Accept call creates a new socket for the incoming connection
    addr_size = sizeof (serverStorage);

    std::cout << COUT_PREFIX << "Proxy\n";

    pthread_t tid = 0;
	while (true) {
        /// socket -> setoptsock -> bind -> listen -> accept -> thread 1
        ///                                                  -> thread 2
        ///                                                  -> thread 3
        new_socket = accept (master_socket, (struct sockaddr *) &serverStorage, &addr_size);
		if (-1 == new_socket) {
			perror( "accept error");
			return 1;
		}

		if (0 != pthread_create(&tid, NULL, packet_handler, (void *)&new_socket)) {
			perror ("Thread Create Error");
			return 1;
		}
		pthread_detach (tid);
	}

    return 0;
}