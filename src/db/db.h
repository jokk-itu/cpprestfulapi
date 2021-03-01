#ifndef H_DB
#define H_DB

#include <cpprest/details/web_utilities.h>

using namespace utility;

class db 
{
public:
    virtual ~db() = 0;
    
protected:
    virtual void open(utility::string_t) = 0;
    virtual void close() = 0;
};

#endif //H_DB