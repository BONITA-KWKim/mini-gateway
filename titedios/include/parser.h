#ifndef __MINI_GW_PARSER_H__
#define __MINI_GW_PARSER_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <iostream>
#include <string>
#include <vector>

#include "mini-gw-common.h"

std::vector<std::pair<std::string, std::string>> parser(std::string message);

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__MINI_GW_PARSER_H__