#include "internal_message_server_main.h"
#include "unistd.h"

void init_web_servers (const string_t &address)
{
	/// URI setting
	uri_builder uri (address);
	uri.append_path (U("/v1/IMS/test/"));
	uri_builder uri_atalk (address);
	uri_atalk.append_path (U("/v1/IMS/kakao-atalk/"));
	uri_builder uri_ftalk (address);
	uri_ftalk.append_path (U("/v1/IMS/kakao-ftalk/"));
	uri_builder uri_mms (address);
	uri_mms.append_path (U("/v1/IMS/mms/"));
	uri_builder uri_sms (address);
	uri_sms.append_path (U("/v1/IMS/sms/"));

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

	std::cout << utility::string_t (U("Listening for ruequest at: ")) << addr << std::endl;
}

void shutdown_web_servers (void)
{
	std::cout << COUT_PREFIX << "Bye-Bye internal message server.\n";

	g_http->close().wait();
	atalk_http->close().wait();
	ftalk_http->close().wait();
	mms_http->close().wait();
	sms_http->close().wait();
}

int init_ipc (void)
{
	std::cout << COUT_PREFIX << "init IPC.\n";
}

void request_to_vendor_for_connecting_mmap (void)
{
	std::cout << COUT_PREFIX << "connection mmap\n";
}

int main (int argc, char *argv[]) 
{
	std::cout << COUT_PREFIX << "Hello internal message server.\n";

	utility::string_t address = U("http://0.0.0.0:");
	utility::string_t port    = U("34568");
	address.append (port);

	/// open web servers
	init_web_servers (address);

	/// setting memory mapped file
	init_ipc ();

	/// request to vendor modules for connecting mmap
	request_to_vendor_for_connecting_mmap ();

	// while (true) {
	// 	/// sleep 5s
	// 	usleep(5000000);
	// }

	std::cout << COUT_PREFIX << "Press ENTER to exit.\n";

	std::string line;
	std::getline (std::cin, line);

	shutdown_web_servers ();

	return 0;
}
 