#ifndef __SERVER_HANDLER_BASE_H__
#define __SERVER_HANDLER_BASE_H__


#include <string>


namespace ns_net
{

class ServerHandlerBase
{
public:
    ServerHandlerBase() {}
    virtual ~ServerHandlerBase() {}

    virtual std::string handle(const std::string& request) = 0; 
};

}

#endif
