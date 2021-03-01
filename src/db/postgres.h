#ifndef H_POSTGRES
#define H_POSTGRES

#include "db.h"
#include <cpprest/details/web_utilities.h>

#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <tuple>
#include <memory>
#include <regex>
#include <string>

using namespace utility;

class postgres : public db
{
public:
    postgres(utility::string_t);
    ~postgres();

    pqxx::result query_n(utility::string_t, int = -1);
    void query_0(utility::string_t);

    template<typename... Args> pqxx::result query_n(utility::string_t, Args..., int = -1);
    template<typename... Args> void query_0(utility::string_t, Args...);

    void setupPreparedQuery(utility::string_t, utility::string_t);

protected:
    void open(utility::string_t) override;
    void close() override;

private:
    std::unique_ptr<pqxx::connection> connection;
};

#endif //H_POSTGRES"