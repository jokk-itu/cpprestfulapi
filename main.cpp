#include <iostream>
#include <exception>
#include <memory>

#include "src/handler.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

void on_config(http_listener_config& config);

std::unique_ptr<handler> g_http_handler;

void on_initialize(const string_t& address)
{
	uri_builder uri(address);

	auto add = uri.to_uri().to_string();
    //http_listener_config config;
    //on_config(config);
    g_http_handler = std::make_unique<handler>(add);
    try 
    {
        if(g_http_handler->open().wait() == pplx::completed) 
            ucout << string_t(U("Listening for requests at: ")) << add << std::endl;
        else
            throw U("Error when opening listener");
    } 
    catch(std::exception &e) 
    {
        ucout << "Error occurred: " << e.what() << endl;
    }      
}
/**
#ifndef WIN_32
void on_config(http_listener_config& config)  
{
    config.set_ssl_context_callback([](boost::asio::ssl::context& context) 
    {
        context.set_options(boost::asio::ssl::context::default_workarounds);
        context.set_password_callback([](std::size_t max_length, boost::asio::ssl::context::password_purpose purpose) 
        {
            return "password";
        });
        context.use_certificate_file("server.crt", boost::asio::ssl::context::pem);
        context.use_private_key_file("server.key", boost::asio::ssl::context::pem);
    });
}
#endif*/

void on_shutdown()
{
    try
    {
        if(g_http_handler->close().wait() == pplx::completed)
            ucout << string_t(U("Closed listener successfully")) << std::endl;
        else
            throw "Error when closing listener";
    }
    catch(std::exception &e) 
    {
        ucout << "Error occurred: " << e.what() << endl;
    }
    
}

#ifdef _WIN32
int main(const int argc, wchar_t* argv[])
#else
int main(const int argc, char* argv[])
#endif
{
    string_t port = U("7070");
    if (argc == 2)
    {
        port = argv[1];
    }

    string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}