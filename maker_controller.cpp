#include "maker_controller.h"

#include <cpprest/json.h>

using namespace web;

void maker_controller::setup_handlers()
{
	request_handlers_[U("/makers/GET")] = [this](http_request& message)
	{
		ucout << "Executed makers GET" << std::endl;
		json::value content;
		content["content"] = json::value::number(20);
		message.reply(status_codes::OK, content).then([this](const pplx::task<void>& t) 
		{
			handle_reply(t);
		});
	};

	request_handlers_[U("/makers/POST")] = [this](http_request& message) 
	{
		ucout << "Executed makers POST" << std::endl;
		message.extract_json().then([this, &message](const pplx::task<json::value>& t) 
		{
			message.reply(status_codes::OK, t.get()).then([this](const pplx::task<void>& t) 
			{
				handle_reply(t);
			});
		});
	};

	request_handlers_[U("/makers/{id}/DELETE")] = [this](http_request& message) 
	{
		ucout << "Executed makers DELETE" << std::endl;
		
		auto query = message.relative_uri().query();
		auto path = message.relative_uri().path();
		auto identifications = find_numbers(path);

		if(query.length() > 0) 
		{
			ucout << "The query: " << query << std::endl;
			auto content = split(query, "&");

			message.reply(status_codes::OK, U("Got the query")).then([this](const pplx::task<void>& t) 
			{
				handle_reply(t);
			});
		}
		else if(identifications.size() != 0) 
		{
			message.reply(status_codes::OK, U("Got the path")).then([this](const pplx::task<void>& t) 
			{
				handle_reply(t);
			});
		}
		else 
		{
			message.extract_json().then([this, &message](const pplx::task<json::value>& t) 
			{
				message.reply(status_codes::OK, t.get()).then([this](const pplx::task<void>& t) 
				{
					handle_reply(t);
				});
			});
		}
	};

	//Add PUT request function
}

maker_controller::maker_controller() : controller()
{}


