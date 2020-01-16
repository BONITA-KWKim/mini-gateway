#include "IMS_atalk.h"

using namespace std;
using namespace web::http::experimental::listener;

IMS_ATALK::IMS_ATALK (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&IMS_ATALK::handle_get, this, std::placeholders::_1));
}

void IMS_ATALK::handle_get (http_request message)
{
	ucout << "Atalk module; GET method" << endl;
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
