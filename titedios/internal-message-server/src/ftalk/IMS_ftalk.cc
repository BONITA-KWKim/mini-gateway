#include "IMS_ftalk.h"

using namespace std;
using namespace web::http::experimental::listener;

IMS_FTALK::IMS_FTALK (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&IMS_FTALK::handle_get, this, std::placeholders::_1));
}

void IMS_FTALK::handle_get (http_request message)
{
	ucout << "Ftalk module; GET method" << endl;
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
