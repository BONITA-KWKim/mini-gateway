#include "IMS_sms.h"

using namespace std;
using namespace web::http::experimental::listener;

IMS_SMS::IMS_SMS (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&IMS_SMS::handle_get, this, std::placeholders::_1));
}

void IMS_SMS::handle_get (http_request message)
{
	ucout << "SMS module; GET method" << endl;
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
