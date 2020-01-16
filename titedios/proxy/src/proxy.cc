#include "proxy.hh"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
/*
* option
*/
int get_options (int argc, char *argv[]) 
{
    int c = -1;
	while (-1 != (c = getopt (argc, argv, "hl:")))
	{
		switch(c) {
		case 'h':		// Show Help message
			show_help();
			return 1;
		case 'l': // Log Level
			gLoglevel = strtol(optarg, NULL, 16);	// Hex string to long
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

/*
* configuration
*/
int get_config(char * configFile) 
{
    // std::ifstream is RAII, i.e. no need to call close
    std::cout << "parse config" << std::endl;

    std::ifstream cFile (configFile);
    if (cFile.is_open()) {
        std::string line;
        while(getline (cFile, line)) {
            if(line[0] == '#' || line.empty())
                continue;

            // get key-value pair
            auto delimiterPos = line.find("=");
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            // insert map
            proxy_env[key]= value;
        }
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }
    return 0;
}

/*
* socket
*/
int init_socket(int port_no) 
{
    /* socket */
    int server_fd; 
    int opt = 1;
    struct sockaddr_in proxy_address;
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

	if (0 > setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
        sizeof(opt))) { 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

    proxy_address.sin_family = AF_INET; 
    proxy_address.sin_addr.s_addr = INADDR_ANY;
    proxy_address.sin_port = htons(port_no); 

    if (0 > bind(server_fd, (struct sockaddr *)&proxy_address, 
        sizeof(proxy_address))) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (0 > listen(server_fd, 3)) { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    return server_fd;
}

int api_call_atalk (void) 
{
    /* test apt call */
    auto fileStream = std::make_shared<ostream>();

    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        // Create http_client to send the request.
        http_client client(U("http://localhost:34568/"));

        // Build request URI and start the request.
        uri_builder builder(U("/v1/IMS/kakao-atalk/"));
        builder.append_query(U("q"), U("cpprestsdk github"));
        return client.request(methods::GET, builder.to_string());
    })

    // Handle response headers arriving.
    .then([=](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        return response.body().read_to_end(fileStream->streambuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
        return fileStream->close();
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }    
}

void *packet_handler(void *arg)
{
    int sockfd = *(int *)arg;

    char buffer[MAX_PACKET_BUFF_SIZE];
    int bytecount;

    int rc = 0;
    std::string parsed_str;
    while (true) {
        if (1 > (rc = event_select(sockfd, 1, 0))) {
            /* no event */
            printf("no event\n");
            continue;
        }

        /* receive socket data */
        rc = recv(sockfd, buffer, MAX_PACKET_BUFF_SIZE, 0);

        if (0 > rc) {
            // peer client is killed
            fprintf(stderr, "Client is killed(0 > recv()): %d\n", errno);
            break;
        }

        if (0 == rc) {
            // peer client is killed
            fprintf(stderr, "Client is killed(0 == recv()): %d\n", errno);
            break;
        }

        printf ("rc: %d\n", rc);
        memset (buffer, 0, MAX_PACKET_BUFF_SIZE);

        printf ("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);

        /* parsing */
        if (0 > parse_telegram(buffer, parsed_str)) {
            std::cerr << "invalid telegram\n";
        }

        /* API call */
        api_call_atalk();

        strcat(buffer, " SERVER ECHO");

        if((bytecount = send(sockfd, buffer, strlen(buffer), 0))== -1){
            fprintf(stderr, "Error sending data %d\n", errno);
        }
        
        printf("Sent bytes %d\n", bytecount);
    }
}

int event_select(int sockfd, int timeoutSec, int timeoutMSec)
{
	struct timeval timeout;
	fd_set         fdset;
	int            rc, so_error;
	socklen_t 	   len;

	timeout.tv_sec  = timeoutSec;   /* Seconds */
	timeout.tv_usec = timeoutMSec;  /* micro Seconds */
	FD_ZERO(&fdset);
	FD_SET (sockfd, &fdset);

	rc = select(sockfd + 1, &fdset, (fd_set *)0, (fd_set *)0, (struct timeval *)&timeout);
	if (rc > 0) {
		// Event occurred
		if (FD_ISSET(sockfd, &fdset)) {
			so_error = -1;
			len      = sizeof(so_error);
			getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
			if (so_error == 0)
				return rc;
		}
	} else {
		// Timeout
	}
	return rc;
}

int parse_telegram(char *buf, std::string result) 
{
    return 0;
}

int main (int argc, char *argv[]) 
{
    /* init */
    /* get options when starting program */
    int result = get_options (argc, argv);
    if (1 == result) return 0;
    else if (0 > result) return -1;

    /* get configuration */
    get_config ("../config/proxy.conf");

    // check environment value
    for (auto it = proxy_env.cbegin(); it != proxy_env.cend(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    /* socket */
    int new_socket = -1;
    int master_socket = -1;
    master_socket = init_socket(8520);
    if (0 > master_socket) {
        perror("master socket");
        exit(1);
    }

    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    //Accept call creates a new socket for the incoming connection
    addr_size = sizeof(serverStorage);

    std::cout << "Proxy\n";

    pthread_t tid = 0;
	while (true) {
        new_socket = accept(master_socket, (struct sockaddr *) &serverStorage, &addr_size);
		if (-1 == new_socket) {
			perror("accept error");
			return 1;
		}

		if (0 != pthread_create(&tid, NULL, packet_handler, (void *)&new_socket)) {
			perror("Thread Create Error");
			return 1;
		}
		pthread_detach(tid);
	}

    return 0;
}