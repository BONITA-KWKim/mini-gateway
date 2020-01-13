#include "my_server.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

MyServer::MyServer (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&MyServer::handle_get, this, std::placeholders::_1));
	m_listener.support (methods::PUT, std::bind(&MyServer::handle_put, this, std::placeholders::_1));
	m_listener.support (methods::POST, std::bind(&MyServer::handle_post, this, std::placeholders::_1));
	m_listener.support (methods::DEL, std::bind(&MyServer::handle_delete, this, std::placeholders::_1));
}

void MyServer::handle_get (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void MyServer::handle_put (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void MyServer::handle_post (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}

void MyServer::handle_delete (http_request message)
{
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
