#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__


#include "SocketBase.h"


namespace ns_net
{

class TcpSocket : public SocketBase
{
public:
    virtual ~TcpSocket() { close(); }
    
    ssize_t read(int socket, char* buf, size_t len)
    {
        ssize_t res = ::read(socket, buf, len);
        _lastErr = (res == -1) ? -1 : 0;
        return res;
    }

    ssize_t write(int socket, char* buf, size_t len)
    {
        ssize_t res = ::write(socket, buf, len);
        _lastErr = (res == -1) ? -1 : 0;
        return res;
    }

protected:
    TcpSocket(DomainType domain)
        : SocketBase(domain, SOCK_STREAM, IPPROTO_TCP)
    {
    }
};

}

#endif
