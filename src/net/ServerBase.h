#ifndef __SERVER_BASE_H__
#define __SERVER_BASE_H__


#include "ListenSocket.h"
#include "ServerHandlerBase.h"


namespace ns_net
{

class ServerBase
{
public:
    ServerBase()
        : _ip("192.168.255.131"),
	    _port(8080),
	    _handler(NULL)
    {
    }

    virtual ~ServerBase() {}

    virtual void run() = 0;

protected:
    virtual ssize_t safeRead(int, std::string&) = 0;
    virtual ssize_t safeWrite(int, const std::string&) = 0;

protected:
    ListenSocket _socket;
    std::string _ip;
    uint16_t _port;
    ServerHandlerBase* _handler;
};

}


#endif
