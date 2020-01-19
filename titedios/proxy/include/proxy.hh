#ifndef __PROXY_H__
#define __PROXY_H__

#ifdef _cplusplus
extern "C"{
#endif

// ========== Header ==========
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <pthread.h>
#include <errno.h>
#include <string>

// ========== JSON ==========
#include "nlohmann/json.hpp"
using json = nlohmann::json;

// ========== Parser ==========
//#include "tao/pegtl.hpp"

/********** define **********/
///
#define MAX_PACKET_BUFF_SIZE 4096
///
#define COUT_PREFIX "[" << __func__ << ":" <<  __LINE__ <<  "] "

int gLoglevel = 0;

/// Get environment key-value pair 
std::map<std::string, std::string> proxy_env;

/// get_options
/// parameter: arguments from starting process
/// result:
///   1: show help
///   0: success
int get_options (int argc, char *argv[]);

/// name: show_help
/// parameter: none
/// result: none
/// 
void show_help (void);

/// name: get_config
/// parameter:
///  config_file: configuration file directory
/// result:
/// 
int get_config (char * configFile);


/// name: init_socket
/// parameter: 
///   int port_no - open port number
/// result:
/// 
int init_socket (int port_no);

int api_call_atalk (void);
void *packet_handler (void *arg);
int event_select (int sockfd, int timeoutSec, int timeoutMSec);

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__PROXY_H__