#ifndef H_MONGO
#define MONGO

#include "db.h"
#include <cpprest/details/web_utilities.h>

#include <memory>
#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class mongo : public db 
{
public:
    mongo(utility::string_t&);
    ~mongo();

    mongocxx::database get_db(utility::string_t&);
    mongocxx::collection get_collection(utility::string_t&, mongocxx::database&);
    void insert(mongocxx::collection&);
    void update_n(mongocxx::collection&, bsoncxx::builder::stream::document&, bsoncxx::builder::stream::document&);
    void update_one(mongocxx::collection&, bsoncxx::builder::stream::document&, bsoncxx::builder::stream::document&);
    void delete_n(mongocxx::collection&, bsoncxx::builder::stream::document&);
    void delete_one(mongocxx::collection&, bsoncxx::builder::stream::document&);

protected:
    void open(utility::string_t) override;
    void close() override;

private:
    std::unique_ptr<mongocxx::instance> instance{};
    std::unique_ptr<mongocxx::client> client;
};

#endif //H_MONGO