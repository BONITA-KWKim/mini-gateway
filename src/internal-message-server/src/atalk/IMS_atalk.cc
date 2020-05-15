#include "IMS_atalk.h"

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
	// msg_record = new MSG_RECORD();
	msg_record = (MSG_RECORD *)util_mmf->attach_MMF(MMF_IDX_PTN,
	                                                O_RDWR | O_CREAT, 
   	                                                MMF_PTN_FILENAME, 
													sizeof(MSG_RECORD) * MAX_ATALK_ENQUEUE, 
			                                        MAX_PTN_RECORDS, 
													0, 
                                                    0, NULL); // MMF
	for (int k = 0; 100 > k; ++k) {
		msg_record[k].status = IDLE;
		memset (msg_record[k].key, 0x00, sizeof(msg_record[k].key));
		memset (msg_record[k].subject, 0x00, sizeof(msg_record[k].subject));
		memset (msg_record[k].receiver, 0x00, sizeof(msg_record[k].receiver));
		memset (msg_record[k].sender_key, 0x00, sizeof(msg_record[k].sender_key));
		memset (msg_record[k].tmpl_code, 0x00, sizeof(msg_record[k].tmpl_code));
		memset (msg_record[k].nation_code, 0x00, sizeof(msg_record[k].nation_code));
		memset (msg_record[k].msg_body, 0x00, sizeof(msg_record[k].msg_body));
	} 	
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
			if (0 != request_to_send_message(request.at("message").as_string())) {
				throw "parsing error";
			} 
			message.reply (status_codes::OK);
		} catch (json::json_exception &e) {
#ifdef DEBUG
			wcout << COUT_PREFIX << e.what() << endl;
#endif
			message.reply (status_codes::BadRequest);
		} catch (http_exception &e) {
#ifdef DEBUG
			wcout << COUT_PREFIX << e.what() << endl;
#endif
			message.reply (status_codes::BadRequest);
		} catch (const char *e) {
#ifdef DEBUG
			wcout << COUT_PREFIX << e << endl;
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

	for (auto const & i: telegram) {
		std::cout << COUT_PREFIX << i.first << ":" << i.second << std::endl;
	}
	/// check required field

	/// enqueue to MMF
	for (int k = 0; MAX_ATALK_ENQUEUE > k; ++k) {
		std::cout << COUT_PREFIX << "index: " << k << 
		" status: " << msg_record[0].status << std::endl;

		if (IDLE == msg_record[k].status) {
			for (auto const & i: telegram) {
				if (0 == strcmp(i.first.c_str(), "KEY")) {
					std::cout << COUT_PREFIX << "key: " << i.second.c_str() << std::endl;
					memcpy (msg_record[k].key, i.second.c_str(), strlen(i.second.c_str()));
				}
			}
			msg_record[k].status = TRANSMIT_REQUEST;
			break;
		}
	} // for (int k = 0; 100 > k; ++k)

	std::cout << COUT_PREFIX << "status: " << msg_record[0].status << " , key: " << msg_record[0].key << std::endl;

	return 0;
}
