#include "internal_message_server.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

IMS::IMS (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&IMS::handle_get, this, std::placeholders::_1));
	m_listener.support (methods::PUT, std::bind(&IMS::handle_put, this, std::placeholders::_1));
	m_listener.support (methods::POST, std::bind(&IMS::handle_post, this, std::placeholders::_1));
	m_listener.support (methods::DEL, std::bind(&IMS::handle_delete, this, std::placeholders::_1));
}

void IMS::handle_get (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void IMS::handle_put (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void IMS::handle_post (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void IMS::handle_delete (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
