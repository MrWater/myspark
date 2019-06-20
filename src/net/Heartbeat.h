#ifndef __HEARTBEAT_H__
#define __HEARTBEAT_H__


#include <string>
#include <assert.h>
#include <memory.h>
#include "PeerSocket.h"


namespace ns_net
{

class Heartbeat
{
public:
    Heartbeat(const std::string& info, std::string ip, uint16_t port) 
        : _port(port),
        _ip(ip),
        _info(info)
    {
        _len = info.size() + 1;
        //if (_len > 1024)
        //    
        
        _sendData = new char[_len];
        memcpy(_sendData, info.c_str(), _len);
        
        _recvData = new char[_len];
        memset(_recvData, 0, _len);

        _socket.bind(ip, port);
        if (_socket.lastErr() == -1)
        {
            // TODO: throw exception
        }
    }
    ~Heartbeat() 
    { 
        delete[] _sendData;
        delete[] _recvData;
    }

    bool sendto(std::string ip, uint16_t port)
    {
        _socket.sendto(_sendData, _len, ip, port);
        if (_socket.lastErr() == -1)
            return false;

        return true;
    }

    bool recvfrom(PeerInfo* info)
    {
        _socket.recvfrom(_recvData, _len, info);

        if (_socket.lastErr() == -1)
        {
            memset(_recvData, 0, _len);
            return false;
        }

        return true;
    }

    bool identify()
    {
        return (strcmp(_sendData, _recvData) == 0);
    }

private:
    PeerSocket _socket;
    char* _sendData;
    char* _recvData;
    size_t _len;
    uint16_t _port;
    std::string _ip;
    std::string _info;
};

}

#endif
