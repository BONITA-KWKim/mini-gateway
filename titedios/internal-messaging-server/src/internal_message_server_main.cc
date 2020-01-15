#include "internal_message_server_main.h"
#include "internal_message_server.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<IMS> g_http;

void on_initialize (const string_t &address)
{
	uri_builder uri (address);
	uri.append_path(U("/v1/IAS/Action/"));

	auto addr = uri.to_uri().to_string();
	g_http = std::unique_ptr<IMS> (new IMS(addr));
	g_http->open().wait();

	std::cout << utility::string_t(U("Listening for rueqeust at: ")) << addr << std::endl;

	return;
}

void on_shutdown (void)
{
	g_http->close().wait();
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
