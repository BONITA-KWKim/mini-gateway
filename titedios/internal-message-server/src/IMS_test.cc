#include "IMS_test.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

IMS_TEST::IMS_TEST (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&IMS_TEST::handle_get, this, std::placeholders::_1));
	m_listener.support (methods::PUT, std::bind(&IMS_TEST::handle_put, this, std::placeholders::_1));
	m_listener.support (methods::POST, std::bind(&IMS_TEST::handle_post, this, std::placeholders::_1));
	m_listener.support (methods::DEL, std::bind(&IMS_TEST::handle_delete, this, std::placeholders::_1));
}

void IMS_TEST::handle_get (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void IMS_TEST::handle_put (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void IMS_TEST::handle_post (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void IMS_TEST::handle_delete (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
