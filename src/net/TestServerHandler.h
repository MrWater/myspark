#ifndef __TEST_SERVER_HANDLER_H__
#define __TEST_SERVER_HANDLER_H__


#include "ServerHandlerBase.h"

namespace ns_net
{

class TestServerHandler : public ServerHandlerBase
{
public:
    TestServerHandler()
        : ServerHandlerBase()
    {
    }

    ~TestServerHandler() {}

    virtual std::string handle(const std::string& request)
    {
        return "test123122222222222222";
    }
};

}


#endif
