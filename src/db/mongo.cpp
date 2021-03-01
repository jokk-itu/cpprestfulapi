#include "mongo.h"

void mongo::open(utility::string_t connection_string)
{
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
}

void mongo::close() 
{
    //disconnect the database/instance
}

mongo::mongo(utility::string_t& connection_string)
{
    open(connection_string);
}

mongo::~mongo() 
{
    close();
}

mongocxx::database mongo::get_db(utility::string_t& database_name)
{
    return client->database(database_name);
}

mongocxx::collection mongo::get_collection(utility::string_t& collection_name, mongocxx::database& database)
{
    return database[collection_name];
}

void mongo::insert(mongocxx::collection& collection)
{
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value values = builder
            << "name" << "MongoDB"
            << bsoncxx::builder::stream::finalize;
    collection.insert_one(values.view());
}

void mongo::update_n(mongocxx::collection& collection, bsoncxx::builder::stream::document& document, bsoncxx::builder::stream::document& update)
{
    collection.update_many(document.view(), update.view());
}

void mongo::update_one(mongocxx::collection& collection, bsoncxx::builder::stream::document& document, bsoncxx::builder::stream::document& update)
{
    collection.update_one(document.view(), update.view());
}

void delete_n(mongocxx::collection& collection, bsoncxx::builder::stream::document& filter)
{
    collection.delete_many(filter.view());
}

void delete_one(mongocxx::collection& collection, bsoncxx::builder::stream::document& filter)
{
    collection.delete_one(filter.view());
}

mongocxx::cursor find_n(mongocxx::collection& collection, bsoncxx::builder::stream::document& filter)
{
    return collection.find(filter.view());
}

bsoncxx::stdx::optional<bsoncxx::document::value> find_one(mongocxx::collection& collection, bsoncxx::builder::stream::document& filter)
{
    return collection.find_one(filter.view());
}