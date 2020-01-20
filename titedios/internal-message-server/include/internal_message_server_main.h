#ifndef __INTERNAL_MESSAGE_SERVER_H__
#define __INTERNAL_MESSAGE_SERVER_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <sys/types.h>
#include <stdio.h>

#include <iostream>

// JSON
#include "nlohmann/json.hpp"
using json = nlohmann::json;

/* MS cplusplus rest SDK */
#include "IMS_test.h"
#include "IMS_base.h"
#include "IMS_atalk.h"
#include "IMS_ftalk.h"
#include "IMS_mms.h"
#include "IMS_sms.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<IMS_TEST> g_http;
std::unique_ptr<IMS_ATALK> atalk_http;
std::unique_ptr<IMS_FTALK> ftalk_http;
std::unique_ptr<IMS_MMS> mms_http;
std::unique_ptr<IMS_SMS> sms_http;

/// 
#define COUT_PREFIX "[" << __func__ << ":" <<  __LINE__ <<  "] "

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__INTERNAL_MESSAGE_SERVER_H__