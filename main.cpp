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
    http_listener_config config;
    on_config(config);
    g_http_handler = std::make_unique<handler>(add, config);
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

#ifndef WIN_32
void on_config(http_listener_config& config)  
{
    config.set_ssl_context_callback([](boost::asio::ssl::context& context) 
    {
        context.set_options(boost::asio::ssl::context::default_workarounds);
        context.set_password_callback([](std::size_t max_length, boost::asio::ssl::context::password_purpose purpose) 
        {
            return "some password";
        });
        try
        {
            context.use_certificate_file("../keys/public.crt", boost::asio::ssl::context::pem);
            context.use_private_key_file("../keys/_private.key", boost::asio::ssl::context::pem);
        }
        catch (exception &e)
        {
            ucout << U("Error occurred on HTTPS config ") << e.what() << std::endl;
        }
    });
}
#endif

void on_shutdown()
{
    try
    {
        if(g_http_handler->close().wait() == pplx::completed)
            ucout << string_t(U("Closed listener successfully")) << std::endl;
        else
            throw U("Error when closing listener");
    }
    catch(std::exception &e) 
    {
        ucout << "Error occurred on shutdown: " << e.what() << endl;
    }
}

#ifdef _WIN32
int main(const int argc, wchar_t* argv[])
#else
int main(const int argc, char* argv[])
#endif
{
    string_t address = argv[1];
    string_t port = argv[2];
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}