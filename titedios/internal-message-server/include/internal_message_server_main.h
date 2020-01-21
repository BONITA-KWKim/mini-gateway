#ifndef __INTERNAL_MESSAGE_SERVER_H__
#define __INTERNAL_MESSAGE_SERVER_H__

#ifdef _cplusplus
extern "C"{
#endif

#include <sys/types.h>
#include <stdio.h>

#include <iostream>

///
#include "mini-gw-common.h"

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

/// name: init_web_servers
/// parameter
///   string_t address: target IP address
/// return: none
/// desc
///   - open http listeners using a IP address and paths. The atalk, ftalk, 
///   mms, sms service is available.
void init_web_servers (const string_t &address);

/// name: shutdown_web_servers
/// parameter: none
/// return: none
/// desc
///   - close all http listeners.
void shutdown_web_servers (void);

/// name: init_ipc
/// parametes: 
/// return:
/// desc
///   - Create IPC and cnofigure it.
int init_ipc (void);

void request_to_vendor_for_connecting_mmap (void);

#ifdef _cplusplus
} // extern "C"
#endif

#endif //__INTERNAL_MESSAGE_SERVER_H__