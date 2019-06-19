#ifndef __UDP_SOCKET_H__
#define __UDP_SOCKET_H__


#include "SocketBase.h"


namespace ns_net
{

class UdpSocket : public SocketBase
{
public:
    virtual ~UdpSocket() { close(); }

    ssize_t recvfrom(char* buf, size_t len, PeerInfo* info)
    {
        ssize_t recv_len = 0;

        if (info != NULL)
        {
            struct sockaddr_in addr;
            socklen_t addr_len = sizeof(addr);
            recv_len = ::recvfrom(_socket, buf, len, 0, (sockaddr*)(&addr), &addr_len);
            _lastErr = (recv_len == -1 ? -1 : 0);

            if (_lastErr != -1)
            {
                info->ip = inet_ntoa(addr.sin_addr);
                info->port = ntohs(addr.sin_port);
            }
        }
        else
        {
            recv_len = ::recvfrom(_socket, buf, len, 0, NULL, NULL);
            _lastErr = (recv_len == -1 ? -1 : 0);
        }

        return recv_len;
    }

    ssize_t sendto(char* buf, size_t len, std::string ip, uint16_t port)
    {
        ssize_t send_len = 0;
        struct sockaddr_in addr;
        addr.sin_family = _domain;
        addr.sin_port = htons(port);
        if (inet_aton(ip.c_str(), &(addr.sin_addr)) == 0)
        {
            _lastErr = -1;
            len = -1;
        }

        send_len = ::sendto(_socket, buf, len, 0, (sockaddr*)(&addr), sizeof(addr));
        _lastErr = (send_len == -1 ? -1 : 0);

        return send_len;
    }

protected:
    UdpSocket(DomainType domain)
        : SocketBase(domain, SOCK_DGRAM, IPPROTO_UDP)
    {
    }
};

}

#endif
