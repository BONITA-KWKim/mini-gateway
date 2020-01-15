#pragma once

#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class IMS
{
public:
	IMS () {}
	IMS (utility::string_t url);

	pplx::task<void> open () { return m_listener.open(); }
	pplx::task<void> close () { return m_listener.close(); }

private:
	void handle_get (http_request msg);
	void handle_put (http_request msg);
	void handle_post (http_request msg);
	void handle_delete (http_request msg);

	http_listener m_listener;
};
