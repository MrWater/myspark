#ifndef __SERVER_H__
#define __SERVER_H__


#include <string>
#include <stdint.h>
#include <queue>
#include <stdlib.h>
#include <mutex>
#include <sys/epoll.h>
#include <thread>
#include <condition_variable>

#include "ListenSocket.h"
#include "ServerContext.h"
#include "ServerHandlerBase.h"
#include "thread/AutoLock.h"


namespace ns_net
{

class Server
{
public:
    Server();
    virtual ~Server();

    void run();

protected:
    virtual ssize_t safeRead(int, std::string&);
    virtual ssize_t safeWrite(int, const std::string&);

private:
    static void threadFunc(Server*);

    void start();
    void initServerSocket();
    
    void addClient(int);
    void closeClient(ServerContext*);

    bool epollCtl(ServerContext*, int, uint32_t);
    bool addReadEvent(ServerContext*, bool modify=false);
    bool addWriteEvent(ServerContext*, bool modify=false);
    bool delEvent(ServerContext*);

    void deal();

    void handleEvent(epoll_event&);
    bool handleReadEvent(ServerContext*);
    bool handleWriteEvent(ServerContext*);

    void ref(ServerContext*);
    void unref(ServerContext*);

    void addUnsolve(ServerContext*);
    ServerContext* fetchUnsolve();

protected:
    uint32_t _workThreadsNum;
    std::string _ip;
    uint16_t _port;
    ServerHandlerBase* _handler;

private:
    ListenSocket _socket;
    int _epollFd;
    std::queue<ServerContext*> _needSolving;
    std::mutex _mtxQueue;
    std::condition_variable _cond;
    
private:
    const size_t _BLOCK_SIZE = 1024;
    const size_t _MAX_CONN = SOMAXCONN;
    const size_t _MAX_EVENTS = 128;
};

}

#endif
