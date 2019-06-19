#ifndef __PEER_SOCKET_H__
#define __PEER_SOCKET_H__


#include "UdpSocket.h"


namespace ns_net
{

class PeerSocket final : public UdpSocket
{
public:
    PeerSocket(DomainType domain)
        : UdpSocket(domain)
    {
    }
    ~PeerSocket() { close(); }
};

}

#endif
