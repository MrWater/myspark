#ifndef __SERVER_H__
#define __SERVER_H__


#include <string>
#include <stdint.h>

#include "ListenSocket.h"
#include "ServerContext.h"
#include "ServerHandlerBase.h"


namespace ns_net
{

class Server
{
public:
    Server();
    virtual ~Server();

    

protected:
    void setHandler(ServerHandlerBase* handler);

private:
    ServerContext* newContext();

private:
    std::string _ip;
    uint16_t _port;
    ServerHandlerBase* _handler;
};

}

#endif
