#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <string>
#include <memory.h>
#include <fcntl.h>


namespace ns_net
{

struct PeerInfo
{
    std::string ip;
    uint16_t port;
};

class SocketBase
{
public:
    typedef int DomainType;
    typedef int SockType;
    typedef int ProtocolType;
    typedef int ShutType;

    virtual ~SocketBase() { close(); }
     
    int lastErr() { return _lastErr; }
    int fd() { return _socket; }

    void bind(std::string ip, uint16_t port)
    {
        // inited?

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));

        addr.sin_family = _domain;
        addr.sin_port = htons(port);
        if (inet_aton(ip.c_str(), &(addr.sin_addr)) == 0)
        {
            _lastErr = -1;
            return;
        }

        _lastErr = ::bind(_socket, (sockaddr*)&addr, sizeof(addr));
    }

    void shutdown(ShutType howto)
    {
        _lastErr = ::shutdown(_socket, howto);
    }

    void close() 
    {
        if (_socket != -1)
        {
            ::close(_socket);
            _socket = -1;
        }
    }

    void setSockOpt(int opt)
    {
        int flag = 1;
        if (setsockopt(_socket, SOL_SOCKET, opt, &flag, sizeof(flag)) == -1)
        {
            _lastErr = -1;
            // TODO: throw exception + errno
        }

        return;
    }

    void setNoBlock() { setSockOpt(O_NONBLOCK); }
    void setNoDelay() { setSockOpt(TCP_NODELAY); }
    void setReuse() { setSockOpt(SO_REUSEADDR); }
    // TODO: other function

protected:
    SocketBase(DomainType domain, SockType type, ProtocolType protocol)
    {
        _domain = domain;
        _socket = socket(domain, type, protocol);
        _lastErr = _socket;
    }

protected:
    int _socket;
    DomainType _domain;
    int _lastErr;
    std::string _localIp;
    uint16_t _port;
};

}

#endif
