#pragma once

#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class IMS_BASE
{
public:
	IMS_BASE () {}
	IMS_BASE (utility::string_t url);

	// pplx::task<void> open () { return m_listener.open(); }
	// pplx::task<void> close () { return m_listener.close(); }

private:
	virtual void handle_get (http_request msg)=0;
	// virtual void handle_put (http_request msg)=0;
	// virtual void handle_post (http_request msg)=0;
	// virtual void handle_delete (http_request msg)=0;

	http_listener m_listener;
};
