#include "IMS_atalk.h"
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 

using namespace std;
using namespace web::http;
using namespace web::http::experimental::listener;

map<utility::string_t, utility::string_t> dictionary;

IMS_ATALK::IMS_ATALK (utility::string_t url) : m_listener (url)
{
	/// define support methods
	m_listener.support (methods::POST, std::bind(&IMS_ATALK::handle_post, this, std::placeholders::_1));

	/// MMF
	util_mmf = new UTILMMF();
	msg_record = (MSG_RECORD *)util_mmf->attach_MMF(MMF_IDX_PTN,
	                                                O_RDWR | O_CREAT, 
   	                                                MMF_PTN_FILENAME, 
													sizeof(MSG_RECORD) * 100, 
			                                        MAX_PTN_RECORDS, 
													0, 
                                                    0, NULL); // MMF
}

void IMS_ATALK::handle_post (http_request message)
{
#ifdef DEBUG
	ucout << COUT_PREFIX << "Atalk module; POST method" << endl;
	ucout << message.to_string() << endl;
#endif
	json::value answer = json::value::array();

	message.extract_json().then([=](json::value request) {
		try {
#ifdef DEBUG
			ucout << COUT_PREFIX << request.at("message").as_string() << endl;
#endif
			/// treat message
			request_to_send_message(request.at("message").as_string());

			message.reply (status_codes::OK);
		} catch (json::json_exception & e) {
#ifdef DEBUG
			wcout << COUT_PREFIX << e.what() << endl;
#endif
			message.reply (status_codes::BadRequest);
		} catch (http_exception & e) {
#ifdef DEBUG
			wcout << COUT_PREFIX << e.what() << endl;
#endif
			message.reply (status_codes::BadRequest);
		}
	});
}

int IMS_ATALK::request_to_send_message(std::string message)
{
#ifdef DEBUG
	ucout << COUT_PREFIX << "input param: " << message << std::endl;
#endif
	/// parsing
	auto telegram = parser(message);

#ifdef DEBUG
	int test = 0;
	for (auto const & i: telegram) {
		std::cout << i.first << ":" << i.second << std::endl;

		msg_record[test].test = test;
		std::cout << COUT_PREFIX << "The number of field: " << 
			msg_record[test].test << std::endl;

		++test;
	}
#endif		
	/// enqueue to MMF


	return 0;
}