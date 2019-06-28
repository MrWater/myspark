#ifndef __SOCKET_OPTION_H__
#define __SOCKET_OPTION_H__


#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>


namespace ns_net
{

class SocketOption
{
public:
    static bool setNoBlock(int fd) { return fcntl(fd, O_NONBLOCK); }
    static bool setNoDelay(int fd) { return setSockOpt(fd, TCP_NODELAY); }
    static bool setReuseAddr(int fd) { return setSockOpt(fd, SO_REUSEADDR); }
    static bool setReusePort(int fd) { return setSockOpt(fd, SO_REUSEPORT); }

private:
    static bool fcntl(int fd, int opt)
    {
        int flags = ::fcntl(fd, F_GETFL, 0);
        ::fcntl(fd, F_SETFL, flags | opt);

        //TODO

        return true;
    }

    static bool setSockOpt(int fd, int opt)
    {
        int flag = 1;
        if (setsockopt(fd, SOL_SOCKET, opt, &flag, sizeof(flag)) == -1)
            return false;

        return true;
    }

private:
    SocketOption() {}
    ~SocketOption() {}
};

}


#endif
