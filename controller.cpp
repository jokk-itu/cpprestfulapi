#include "controller.h"

#include "maker_controller.h"

void controller::setup_handlers()
{
	controllers_.push_back(std::make_unique<maker_controller>());

	for (auto& c : controllers_)
	{
		c->setup_handlers();
		request_handlers_.insert(c->request_handlers_.begin(), c->request_handlers_.end());
	}
}

void controller::do_request(const utility::string_t& path, http_request &message)
{
	try 
	{
		auto &request_handler = request_handlers_.at(path);
		request_handler(message);
		ucout << "do_request done" << std::endl;
	}
	catch(...) 
	{
		message.reply(status_codes::NotFound).then([this](const pplx::task<void> &t)
			{
				handle_reply(t);
			});
	}	
}

void controller::handle_reply(const pplx::task<void> &t)
{
	try
	{
		if(!t.is_done())
			throw std::logic_error("handle_reply() is called in a .then function appending a task");

		t.get();
	}
	catch(std::exception &e)
	{
		ucout << e.what() << std::endl;
	}
}

std::vector<utility::string_t> controller::split(utility::string_t content, utility::string_t delimeter) 
{
    auto start = 0U;
    auto end = content.find(delimeter);
    std::vector<std::string> split_content;
    while (end != std::string::npos)
    {
        split_content.push_back(content.substr(start, end - start));
        start = end + delimeter.length();
        end = content.find(delimeter, start);
    }
    return split_content;
}

std::smatch controller::find_numbers(utility::string_t& path) 
{
	std::regex pattern("[\\d]+");
    std::smatch matches;
    regex_search(path, matches, pattern);
	return matches;
}

utility::string_t vtostring(std::vector<utility::string_t>& v) 
{
	utility::string_t s;
	for(auto& str : v) 
	{
		s += str;
	}
	return s;
}