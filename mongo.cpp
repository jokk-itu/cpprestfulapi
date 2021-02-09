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

mongo::mongo(utility::string_t connection_string) 
{
    open(connection_string);
}

mongo::~mongo() 
{
    close();
}


mongocxx::database mongo::get_db(utility::string_t database_name) 
{
    return client->database(database_name);
}

mongocxx::collection mongo::get_collection(utility::string_t collection_name, mongocxx::database database) 
{
    return database[collection_name];
}

//insert document

//update document

//delete document

//learn about querying documents and make up your mind from that