#pragma once

#include "IMS_base.h"
#include "parser.h"

#define DEBUG

class IMS_ATALK : IMS_BASE
{
public:
	IMS_ATALK () {}
	IMS_ATALK (utility::string_t url);

	pplx::task<void> open () { return m_listener.open(); }
	pplx::task<void> close () { return m_listener.close(); }

private:
	// void handle_get (http_request msg);
	// void handle_put (http_request msg);
	void handle_post (http_request msg);
	// void handle_delete (http_request msg);
	std::vector<utility::string_t> requestPath(const http_request & message) ;
	int request_to_send_message(std::string message);

	http_listener m_listener;
};
