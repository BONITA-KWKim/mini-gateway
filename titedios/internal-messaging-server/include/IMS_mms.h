#pragma once

#include "IMS_base.h"

class IMS_MMS : IMS_BASE
{
public:
	IMS_MMS () {}
	IMS_MMS (utility::string_t url);

	pplx::task<void> open () { return m_listener.open(); }
	pplx::task<void> close () { return m_listener.close(); }

private:
	void handle_get (http_request msg);
	// void handle_put (http_request msg);
	// void handle_post (http_request msg);
	// void handle_delete (http_request msg);

	http_listener m_listener;
};
