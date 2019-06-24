#ifndef __SERVER_CONTEXT_H__
#define __SERVER_CONTEXT_H__


#include "ProtocolBase.h"


namespace ns_net
{

class ServerContext
{
public:
    ServerContext() {}
    virtual ~ServerContext() {}

public:
    int _fd;
    ProtocolBase* _requestProtocol;
    ProtocolBase* _responseProtocol;
};

}

#endif
