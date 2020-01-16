#include "internal_message_server_main.h"

void on_initialize (const string_t &address)
{
	/* URI setting */
	uri_builder uri (address);
	uri.append_path(U("/v1/IMS/test/"));
	uri_builder uri_atalk (address);
	uri_atalk.append_path(U("/v1/IMS/kakao-atalk/"));
	uri_builder uri_ftalk (address);
	uri_ftalk.append_path(U("/v1/IMS/kakao-ftalk/"));
	uri_builder uri_mms (address);
	uri_mms.append_path(U("/v1/IMS/mms/"));
	uri_builder uri_sms (address);
	uri_sms.append_path(U("/v1/IMS/sms/"));

	auto addr = uri.to_uri().to_string();
	auto atalk_addr = uri_atalk.to_uri().to_string();
	auto ftalk_addr = uri_ftalk.to_uri().to_string();
	auto mms_addr = uri_mms.to_uri().to_string();
	auto sms_addr = uri_sms.to_uri().to_string();

	g_http = std::unique_ptr<IMS_TEST> (new IMS_TEST(addr));
	g_http->open().wait();
	atalk_http = std::unique_ptr<IMS_ATALK> (new IMS_ATALK(atalk_addr));
	atalk_http->open().wait();
	ftalk_http = std::unique_ptr<IMS_FTALK> (new IMS_FTALK(ftalk_addr));
	ftalk_http->open().wait();
	mms_http = std::unique_ptr<IMS_MMS> (new IMS_MMS(mms_addr));
	mms_http->open().wait();
	sms_http = std::unique_ptr<IMS_SMS> (new IMS_SMS(sms_addr));
	sms_http->open().wait();

	std::cout << utility::string_t(U("Listening for rueqeust at: ")) << addr << std::endl;

	return;
}

void on_shutdown (void)
{
	g_http->close().wait();
	atalk_http->close().wait();
	ftalk_http->close().wait();
	mms_http->close().wait();
	sms_http->close().wait();

	return;
}

int main (int argc, char *argv[]) 
{
    printf ("Hello interanp API server.\n");

	utility::string_t port = U("34568");
	if (2 == argc) {
		port = argv[1];
	}

	//utility::string_t address = U("http://localhost:");
	utility::string_t address = U("http://0.0.0.0:");
	address.append (port);

	on_initialize (address);
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline (std::cin, line);

	on_shutdown ();
	return 0;
}
