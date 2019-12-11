#ifndef __PROXY_H__
#define __PROXY_H__

#ifdef _cplusplus
extern "C"{
#endif

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

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#define MAX_PACKET_BUFF_SIZE 4096

int gLoglevel = 0;
std::map<std::string, std::string> proxy_env;

int get_options(int argc, char *argv[]);
int get_config(char * configFile);
void show_help(void);
int init_socket(int port_no);
void *packet_handler(void *arg);
int event_select(int sockfd, int timeoutSec, int timeoutMSec);
int parse_telegram(char *buf, std::string result);

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__PROXY_H__