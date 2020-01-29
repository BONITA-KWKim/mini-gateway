#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

int main(int argc, char* argv[])
{
    auto fileStream = std::make_shared<ostream>();

    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        // // Create http_client to send the request.
        // http_client client(U("http://localhost:34568/"));

        // // Build request URI and start the request.
        // uri_builder builder(U("/MyServer/Action/"));
        // builder.append_query(U("q"), U("cpprestsdk github"));
        // return client.request(methods::GET, builder.to_string());

        http_client client (U("http://localhost:34568/"));
        uri_builder builder (U("/v1/IMS/"));
        builder.append_path (U("kakao-atalk"));

        json::value json_telegram;
        json_telegram[U("message")] = json::value::string (U("KEY:a000000001\r\nEXTEND:\r\nSUBJECT:subject\r\nRECEIVER:01077770000\r\nSENDER:\r\n" \
"SENDERKEY:1234abcd5678efgh\r\nTMPLCD:mts_test_0001\r\nNATIONCODE:82\r\nMDATA:MIME-Version: 1.0\r\n" \
"MDATA:Content-Type: multipart/mixed;boundary=\"----=_NextPart_000_0049_01C851E9.827BA430\"\r\n" \
"MDATA:\r\nMDATA:------=_NextPart_000_0049_01C851E9.827BA430\r\n" \
"MDATA:Content-Type: TXT;charset=\"ks_c_5601-1987\"\r\nMDATA:Content-Transfer-Encoding: base64\r\n" \
"MDATA:Content-Svc: ALL;\r\nMDATA:\r\n" \
"MDATA:bWFpbA0KDQoNCqahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGm\r\n" \
"MDATA:oaahpqEgICANCktza3lCDQqws7nfxsAgsejAur+1IC8gwvfA5SAgIA0KRW1haWwgOiBqb2xpQGtz\r\n" \
"MDATA:a3liLmNvbQ0KwPzIrSA6IDA3MC03MDE2LTk5ODMgIMbRvbogOiAwMi01NjUtOTQ2Nw0KSC5QIDog\r\n" \
"MDATA:MDE5LTI3MC03OTE4DQqmoaahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGmoaahpqGm\r\n" \
"MDATA:oaahpqGmoaah\r\nMDATA:\r\nMDATA:------=_NextPart_000_0049_01C851E9.827BA430\r\n" \
"MDATA:\r\nEND\r\n"));


        http_request req(methods::POST);
        req.set_request_uri(builder.to_string());
        req.set_body(json_telegram);

        return client.request (req);
    })

    // Handle response headers arriving.
    .then([=](http_response response)
    {
        printf("Received response status code:%u\n", response.status_code());

        // Write response body into the file.
        return response.body().read_to_end(fileStream->streambuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
        return fileStream->close();
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        printf("Error exception:%s\n", e.what());
    }

    return 0;
}