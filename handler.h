#ifndef HANDLER_H
#define HANDLER_H


#include <string>
#include <memory>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/producerconsumerstream.h"
#include <cpprest/http_client.h>
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"

#include "controller.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace concurrency::streams;


class handler
{
public:
    handler(utility::string_t); //HTTP
    handler(utility::string_t, http_listener_config); //HTTPS
    ~handler() = default;
    

    pplx::task<void>open() { return m_listener.open(); }
    pplx::task<void>close() { return m_listener.close(); }

private:
    handler();

    void handle_request(http_request message);

    http_listener m_listener;
    std::unique_ptr<controller> request_router;
};

#endif // HANDLER_H