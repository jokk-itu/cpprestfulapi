#ifndef H_CONTROLLER
#define H_CONTROLLER

#include <unordered_map>
#include <string>
#include <functional>
#include <cpprest/http_client.h>
#include <vector>
#include <regex>

using namespace web::http;

class controller
{
public:
	controller() = default;
	virtual ~controller() = default;
	virtual void setup_handlers();
	void do_request(const utility::string_t&, http_request&);
	void handle_reply(const pplx::task<void> &t);
	std::vector<utility::string_t> split(utility::string_t content, utility::string_t delimeter);
	std::smatch find_numbers(utility::string_t &);
	utility::string_t vtostring(std::vector<utility::string_t>&);

protected:
	std::unordered_map<utility::string_t, std::function<void(http_request&)>> request_handlers_;

private:
	std::vector<std::unique_ptr<controller>> controllers_;
	
};

#endif //H_CONTROLLER
