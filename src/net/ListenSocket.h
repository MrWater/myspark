#ifndef __LISTEN_SOCKET_H__
#define __LISTEN_SOCKET_H__


#include "TcpSocket.h"


namespace ns_net
{

class ListenSocket : public TcpSocket
{
public:
    ListenSocket(DomainType domain=AF_INET)
        : TcpSocket(domain)
    {
    }
    virtual ~ListenSocket() { close(); }

    void listen(int backlog=10)
    {
        _lastErr = ::listen(_socket, backlog);
    }

    int accept(PeerInfo* info)
    {
        int socket = -1;

        if (info != NULL)
        {
            sockaddr_in addr;
            uint32_t len = sizeof(addr);
            socket = ::accept(_socket, (sockaddr*)(&addr), &len);
            _lastErr = (socket == -1 ? -1 : 0);

            if (_lastErr != -1)
            {
                info->ip = inet_ntoa(addr.sin_addr);
                info->port = ntohs(addr.sin_port);
            }
        }
        else
        {
            socket = ::accept(_socket, NULL, NULL);
            _lastErr = (socket == -1 ? -1 : 0);
        }

        return socket;
    }
};

}

#endif
