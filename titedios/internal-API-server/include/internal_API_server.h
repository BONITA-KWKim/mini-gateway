#ifndef __INTERNAL_API_SERVER_H__
#define __INTERNAL_API_SERVER_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <sys/types.h>
#include <stdio.h>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__INTERNAL_API_SERVER_H__