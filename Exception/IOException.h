#ifndef __IO_EXCEPTION_H__
#define __IO_EXCEPTION_H__

#include <exception>


namespace ns_exception
{

class IOException : public std::exception
{
public:
    IOException(const char* ex) : _description(ex) {}
    
    const char* what() const throw() { return _description; } 

private:
    const char* _description;
};

}

#endif
