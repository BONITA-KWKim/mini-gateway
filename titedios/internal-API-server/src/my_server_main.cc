#include <stdafx.h>
#include "my_server.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<MyServer> g_http;

void on_initialize (const string_t &address)
{
	uri_builder uri(address);
	uri.append_path(U("MyServer/Action/"));

	auto addr = uri.to_uri().to_string();
	g_http = std::unique_ptr<MyServer> (new MyServer(add));
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
	utility::string_t port = U("34568");
	if (2 == argc) {
		port = argv[1];
	}

	utility::string_t address = U("http://localhost:");
	address.append(port);

	on_initilize(address);
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);

	on_shutdown();
	return 0;
}
