#include "IMS_atalk.h"
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 

using namespace std;
using namespace web::http::experimental::listener;

IMS_ATALK::IMS_ATALK (utility::string_t url) : m_listener (url)
{
	m_listener.support (methods::POST, std::bind(&IMS_ATALK::handle_post, this, std::placeholders::_1));
}

void IMS_ATALK::handle_post (http_request message)
{
	ucout << "Atalk module; POST method" << endl;
	ucout << message.to_string() << endl;

	/*
    string input(message.to_string()); 

    vector<string> result; 
    boost::split(result, input, boost::is_any_of("\r\n")); 
  
    for (int i = 0; i < result.size(); i++) 
        ucout << result[i] << endl; 
	*/

	message.reply (status_codes::OK, message.to_string());
}
