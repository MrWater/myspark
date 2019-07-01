#include <sstream>

#include "AIOServer.h"
#include "SocketOption.h"

#include <iostream>

using namespace std;
using namespace ns_net;

AIOServer::AIOServer()
	: ServerBase(), 
    _workThreadsNum(10)
{
}

AIOServer::~AIOServer()
{
	unique_lock<mutex> lock(_mtxQueue);
	while (!_needSolving.empty())
	{
		unref(_needSolving.front());
		_needSolving.pop();
	}
}

void
AIOServer::run()
{
	initServerSocket();
	_epollFd = epoll_create(_MAX_EVENTS);

	ServerContext* ctx = new ServerContext;
    ctx->_fd = _socket.get();

	if (!epollCtl(ctx, EPOLL_CTL_ADD, EPOLLIN))
	{
		// TODO: log
        return;
	}

    for (size_t i = 0; i < _workThreadsNum; ++i)
    {
        thread t(AIOServer::threadFunc, this);
        t.detach();
    }

    start();
}

void
AIOServer::threadFunc(AIOServer* server)
{
	assert(server != NULL);
	server->deal();
}

void
AIOServer::start()
{
	epoll_event events[_MAX_EVENTS];
	int eventNum = 0;
	int clientFd = 0;
	
	while (true)
	{
		eventNum = epoll_wait(_epollFd, events, _MAX_EVENTS, -1);
		
        if(eventNum < 0 && errno != EINTR)
		{
			// TODO:throw
			exit(1);
		}

		for (int i = 0; i < eventNum; ++i)
		{
			if (((ServerContext*)(events[i].data.ptr))->_fd == _socket.get())
			{
				while((clientFd = _socket.accept(NULL)) >= 0)
				{
                    addClient(clientFd);
				}

				if(errno != EAGAIN && errno != EWOULDBLOCK && errno != ECONNABORTED && errno != EINTR && errno != EPROTO)
				{
					// TODO: throw
					
				}
			}
			else
			{
				handleEvent(events[i]);
			}
		}
	}
}

void
AIOServer::initServerSocket()
{
	_socket.setReuseAddr();
	if (_socket.lastErr() == -1)
	{
		exit(1);
	}
	
	_socket.setNoDelay();
	if (_socket.lastErr() == -1)
	{
		exit(1);
	}

	_socket.bind(_ip, _port);
	if (_socket.lastErr() == -1)
	{
		exit(1);
	}
	
    _socket.setNoBlock();
	if (_socket.lastErr() == -1)
	{
		exit(1);
	}

	_socket.listen(_MAX_CONN);
	if (_socket.lastErr() == -1)
	{
		exit(1);
	}
}

ssize_t
AIOServer::safeRead(int fd, string& request)
{
	char buf[_BLOCK_SIZE+1];
	ostringstream oss;
	ssize_t len = _socket.read(fd, buf, _BLOCK_SIZE);

	if (_socket.lastErr() == -1)
	{
		//TODO: log
	}

    buf[len] = 0;
	oss << buf;
	request = oss.str();

	return len;
}

ssize_t
AIOServer::safeWrite(int fd, const string& response)
{
    size_t len = response.length();
    char buf[len];
    memcpy(buf, response.c_str(), len);

	ssize_t ret = _socket.write(fd, buf, len);
	if (_socket.lastErr() == -1)
	{
		// TODO: log
	}

	return ret;
}

bool
AIOServer::epollCtl(ServerContext* ctx, int op, uint32_t events)
{
	assert(ctx != NULL);

	epoll_event ev;
	bzero(&ev, sizeof(ev));
	ev.data.ptr = ctx;
	ev.events = events;
	if (epoll_ctl(_epollFd, op, ctx->_fd, &ev) < 0) 
	{
		return false;
	}

	return true;
}

void
AIOServer::addClient(int clientFd)
{
    ServerContext* ctx = new ServerContext;
    ctx->_fd = clientFd;
    ref(ctx);
    SocketOption::setNoBlock(clientFd);
    SocketOption::setNoDelay(clientFd);
    
    if (!addReadEvent(ctx))
    {
        closeClient(ctx);
    }
}

void
AIOServer::closeClient(ServerContext* ctx)
{
	assert(ctx != NULL);

	close(ctx->_fd);
    assert(ctx->_refTimes == 1);
	unref(ctx);

	ctx = NULL;
}
bool 
AIOServer::addReadEvent(ServerContext* ctx, bool modify)
{
	assert(ctx != NULL);

    int op = modify ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;

	if (!epollCtl(ctx, op, EPOLLIN|EPOLLERR|EPOLLHUP))
	{
        //TODO
        return false;
	}

    return true;
}

bool
AIOServer::addWriteEvent(ServerContext* ctx, bool modify)
{
	assert(ctx != NULL);	
    
    int op = modify ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;

	if (!epollCtl(ctx, op, EPOLLOUT|EPOLLERR|EPOLLHUP))
	{
        return false;
	}

    return true;
}

bool
AIOServer::delEvent(ServerContext* ctx)
{
    if (!epollCtl(ctx, EPOLL_CTL_DEL, 0))
    {
        //TODO
        return false;
    }

    return true;
}

void
AIOServer::deal()
{
	while (true)
	{
		ServerContext* ctx = fetchUnsolve();

		ctx->clear();
		string request = "";
		ssize_t rdbytes = safeRead(ctx->_fd, request);

		if (rdbytes == 0)
		{
            closeClient(ctx);
            continue;
		}

		assert(_handler != NULL);
		string response = "";

		try
		{
			response = _handler->handle(request);
		}
		catch (exception& e)
		{
            cout << e.what() << endl;
			closeClient(ctx);
			// TODO:
		}

		ctx->_request = request;
		ctx->_response = response;

        if (!addWriteEvent(ctx))
        {
            closeClient(ctx);
            ctx = NULL;
        }
	}
}

void
AIOServer::handleEvent(epoll_event& event)
{
	ServerContext* ctx = reinterpret_cast<ServerContext*>(event.data.ptr);

	if (event.events & (EPOLLERR | EPOLLHUP))
	{
        delEvent(ctx);
		closeClient(ctx);
	}
	else if (event.events & EPOLLIN)
	{
		if (!handleReadEvent(ctx))
			closeClient(ctx);
	}
	else
	{
		if (!handleWriteEvent(ctx))
			closeClient(ctx);
	}		
}

bool
AIOServer::handleReadEvent(ServerContext* ctx)
{
    // TODO: return
	assert(ctx != NULL);

    if (!delEvent(ctx))
    {
        return false;
    }
	
    addUnsolve(ctx);
    unref(ctx);

    return true;
}

bool
AIOServer::handleWriteEvent(ServerContext* ctx)
{
    assert(ctx != NULL);

    ssize_t wtbytes = safeWrite(ctx->_fd, ctx->_response);
    if (wtbytes == -1)
    {
        // TODO
        return false;
    }

    // TODO: return
    if (!addReadEvent(ctx, true))
    {
        return false;
    }

    return true;
}

void
AIOServer::ref(ServerContext* ctx)
{
	assert(ctx != NULL);
	ctx->_refTimes += 1;
}

void
AIOServer::unref(ServerContext* ctx)
{
	assert(ctx != NULL);
	ctx->_refTimes -= 1;

	if (ctx->_refTimes == 0)
		delete ctx;
}

void
AIOServer::addUnsolve(ServerContext* ctx)
{
	assert(ctx != NULL);
	ref(ctx);
	
	unique_lock<mutex> lock(_mtxQueue);
	_needSolving.push(ctx);
    _cond.notify_all();
}

ServerContext*
AIOServer::fetchUnsolve()
{
	unique_lock<mutex> lock(_mtxQueue);
    cout << "size: " << _needSolving.size() << endl;

	while (_needSolving.empty())
	{
		_cond.wait(lock);
	}

	ServerContext* ctx = _needSolving.front();
	_needSolving.pop();

	return ctx;
}
