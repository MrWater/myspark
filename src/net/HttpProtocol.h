#ifndef __HTTP_PROTOCOL_H__
#define __HTTP_PROTOCOL_H__


#include <map>
#include "ProtocolBase.h"


namespace ns_net
{

class HttpProtocol : public ProtocolBase
{
public:
    HttpProtocol()
    {
    }
    virtual ~HttpProtocol() {}

private:
    std::string _method;
    std::string _uri;
    std::string _ver;
     
};

}

#endif
