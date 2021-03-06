#include "handler.h"
#include "controllers/maker_controller.h"
#include "controllers/controller.h"

#include <regex>
#include <utility>

void replace_numbers(utility::string_t& path);
void add_http_method(utility::string_t& path, http::method& method);

handler::handler(const utility::string_t& url) : m_listener(url)
{
    m_listener.support(std::bind(&handler::handle_request, this, std::placeholders::_1));
    ucout << "Listener is loaded" << std::endl;
    request_router = std::make_unique<controller>();
    request_router->setup_handlers();
    ucout << "MethodRouter is loaded" << std::endl;   
}

handler::handler(const utility::string_t& url, http_listener_config config) :m_listener(url, std::move(config))
{
    m_listener.support(std::bind(&handler::handle_request, this, std::placeholders::_1));
    ucout << "Listener is loaded" << std::endl;
    request_router = std::make_unique<controller>();
    request_router->setup_handlers();
    ucout << "MethodRouter is loaded" << std::endl;   
}

void handler::handle_request(http_request message) 
{
    ucout << "The message received: " << message.to_string() << std::endl;
    ucout << "Relative path encoded is: " << message.relative_uri().path() << std::endl;
    auto path = message.relative_uri().path();
    auto method = message.method();
    add_http_method(path, method);
    replace_numbers(path);
    request_router->do_request(path, message);
}

/**
 * The function has been tested  
*/
void replace_numbers(utility::string_t& path) 
{
    std::regex pattern("[\\d]+");
    std::smatch matches;
    regex_search(path, matches, pattern);

    if(matches.length() <= 1)
        return;
    
    auto position = 0;
    for(auto& match : matches) 
    {
        position = path.find(match);
        path.replace(position, match.length(), "{id}");
    }
}

void add_http_method(utility::string_t& path, http::method& method) 
{
    if(path.at(path.length()-1) != '/')
        path.push_back('/');

    if(method == U("GET"))
        path += U("GET");

    else if(method == U("POST"))
        path += U("POST");

    else if(method == U("PUT"))
        path += U("PUT");

    else if(method == U("DELETE"))
        path += U("DELETE");

    else
      throw U("The given HTTP method is not supported");
}