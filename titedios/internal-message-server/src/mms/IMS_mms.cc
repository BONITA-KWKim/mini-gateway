#include "IMS_mms.h"

using namespace std;
using namespace web::http::experimental::listener;

IMS_MMS::IMS_MMS (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::GET, std::bind(&IMS_MMS::handle_get, this, std::placeholders::_1));
}

void IMS_MMS::handle_get (http_request message)
{
	ucout << "MMS module; GET method" << endl;
	ucout << message.to_string() << endl;
	message.reply (status_codes::OK);
}
