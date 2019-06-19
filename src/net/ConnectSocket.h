#ifndef __CONNECT_SOCKET_H__
#define __CONNECT_SOCKET_H__


#include "TcpSocket.h"


namespace ns_net
{

class ConnectSocket : public TcpSocket
{
public:
    ConnectSocket(DomainType domain)
        : TcpSocket(domain)
    {
    }
    virtual ~ConnectSocket() { close(); }

    void connect(std::string ip, uint16_t port)
    {
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));

        addr.sin_family = _domain;
        addr.sin_port = htons(port);
        if (inet_aton(ip.c_str(), &(addr.sin_addr)) == 0)
        {
            _lastErr = -1;
            return;
        }

        _lastErr = ::connect(_socket, (sockaddr*)(&addr), sizeof(addr));
    }
};

}

#endif
