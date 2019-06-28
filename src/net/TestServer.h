#ifndef __TEST_SERVER_H__
#define __TEST_SERVER_H__


#include "Server.h"
#include "TestServerHandler.h"


namespace ns_net
{

class TestServer : public Server
{
public:
    TestServer()
        : Server()
    {
        _handler = dynamic_cast<ServerHandlerBase*>(new TestServerHandler);
    }

    ~TestServer() 
    {
        delete _handler;
    }
};

}

#endif
