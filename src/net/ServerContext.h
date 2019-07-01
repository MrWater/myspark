#ifndef __SERVER_CONTEXT_H__
#define __SERVER_CONTEXT_H__


#include <string>

#include "ProtocolBase.h"


namespace ns_net
{

class Server;
class AIOServer;

class ServerContext
{
public:
    enum class Mode : unsigned char
    {
        UNDEFINED,
        READ,
        WRITE
    };

public:
    ServerContext() 
        :_fd(-1),
        _request(""),
        _response(""),
        _refTimes(0),
        _writtenBytes(0),
        _mode(Mode::UNDEFINED)
    {
    }
    virtual ~ServerContext() {}

public:
    void clear()
    {
        _request = "";
        _response = "";
    }

private:
    int _fd;

public:
    std::string _request;
    std::string _response;

private:
    size_t _refTimes;
    ssize_t _writtenBytes;
    Mode _mode;
    friend class Server;
    friend class AIOServer;
};

}

#endif
