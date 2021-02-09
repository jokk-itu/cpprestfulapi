#include "postgres.h"

void postgres::close() 
{
    connection->disconnect();
}

void postgres::open(utility::string_t connection_string) 
{
    connection = std::make_unique<pqxx::connection>(connection_string);
}

postgres::postgres(utility::string_t connection_string)
{
    open(connection_string);
}

postgres::~postgres() 
{
    close();
}


void postgres::setupPreparedQuery(utility::string_t name, utility::string_t query) 
{    
    connection->prepare(name, query);
}


pqxx::result postgres::query_n(utility::string_t query, const int rows) 
{
    pqxx::work worker{*connection};
    auto results = worker.exec(query);
    worker.commit();
    return results;
}

void postgres::query_0(utility::string_t query) 
{
    pqxx::work worker{*connection};
    worker.exec0(query);
    worker.commit();
}


//This badboy needs to be tested
template<typename... Args>
pqxx::result postgres::query_n(utility::string_t name, Args... args, const int rows) 
{
    if(rows == 0)
        throw std::logic_error(U("query_n() returns a result, if it isn't desired use query_0()"));

    pqxx::work worker{*connection};
    if(!worker.prepared(name).exists())
        throw U("The prepared query does not exist. Create it beforehand with setupPreparedQuery()");

    pqxx::result results;
    if(rows < 0) 
        results = worker.exec_prepared(name, args...);
    else if(rows == 1)
        results = worker.exec_prepared1(name, args...);
    else
        results = worker.exec_prepared_n(rows, name, args...);

    worker.commit();
    return results;
}

//This badboy needs to be tested
template<typename... Args>
void postgres::query_0(utility::string_t name, Args... args) 
{    
    pqxx::work worker{*connection};
    if(!worker.prepared(name).exists())
        throw "The prepared query does not exist. Create it beforehand with setupPreparedQuery()";

    auto result = worker.exec_prepared0(name, args...);
    worker.commit();
}