#include "proxy.hh"

int gLoglevel = 0;
std::map<std::string, std::string> proxy_env;

int get_options(int argc, char *argv[]);
int get_config(char * configFile);
void show_help(void);
int init_socket(int prot_no);

int get_options(int argc, char *argv[]) {
    int c = -1;
	while (-1 != (c = getopt(argc, argv, "hl:")))
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

void show_help(void) {
	fprintf(stdout, "proxy [-h] [-l log_level] \r\n");
	fprintf(stdout, "    -h: Show help\n");
	fprintf(stdout, "    -l: Log level (hex string)\n");
}

int get_config(char * configFile) {
    // std::ifstream is RAII, i.e. no need to call close
    std::cout << "parse config" << std::endl;

    std::ifstream cFile (configFile);
    if (cFile.is_open()) {
        std::string line;
        while(getline(cFile, line)) {
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

int init_socket(int prot_no) {
    /* connect socket */
    int server_fd, new_socket, valread; 
    struct sockaddr_in serverAddr;

	// [[ Setup for Socket ]]
	// ************************
	// Configure settings of the server address struct
	// Address family = Internet
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);   // inet_addr("127.0.0.1");	//Set IP address to localhost
	serverAddr.sin_port        = htons(prot_no);				// Set port number, using htons function to use proper byte order

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    return 0;
}

int main(int argc, char *argv[]) {
    /* init */
    int result = get_options(argc, argv);
    if (1 == result) return 0;
    else if (0 > result) return -1;

    get_config("/Users/mts.dev/Documents/Bonita.E/workspace/Docker/"\
        "mini-gateway/titedios/gw-proxy/config/proxy.conf");

    // check environment value
    for(auto it = proxy_env.cbegin(); it != proxy_env.cend(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    init_socket(9010);
    
    return 0;
}