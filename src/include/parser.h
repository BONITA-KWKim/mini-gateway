#ifndef __MINI_GW_PARSER_H__
#define __MINI_GW_PARSER_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <iostream>
#include <string>
#include <vector>

#include "mini-gw-common.h"
#include "base64.h"

#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 

#define MDATA_STATES_INIT       90
#define MDATA_STATES_HEADER     91
#define MDATA_STATES_SUB_HEADER 92
#define MDATA_STATES_MAIN       93
#define MDATA_STATES_END        94

#define LENGTH_MIME_VERSION  5
#define LENGTH_TYPE          10
#define LENGTH_CHARSET       20
#define LENGTH_ENCODING      10
#define LENGTH_MSG_BODY      4000

typedef struct _MDATA {
    char mime_version[LENGTH_MIME_VERSION];
    char type[LENGTH_TYPE];
    char charset[LENGTH_CHARSET];
    char encoding[LENGTH_ENCODING];
    char message_body[LENGTH_MSG_BODY];
} MDATA;

std::vector<std::pair<std::string, std::string>> parser(std::string message);
int extractMDATA(int *state, std::string raw_message);

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__MINI_GW_PARSER_H__