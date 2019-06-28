#include <sstream>

#include "Server.h"
#include "SocketOption.h"

#include <iostream>

using namespace std;
using namespace ns_net;

Server::Server()
	: _workThreadsNum(10),
	_ip("127.0.0.1"),
	_port(8080),
	_handler(NULL)
{
}

Server::~Server()
{
	unique_lock<mutex> lock(_mtxQueue);
	while (!_needSolving.empty())
	{
		unref(_needSolving.front());
		_needSolving.pop();
	}
}

void
Server::run()
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
        thread t(Server::threadFunc, this);
        t.detach();
    }

    start();
}

void
Server::threadFunc(Server* server)
{
	assert(server != NULL);
	server->deal();
}

void
Server::start()
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
Server::initServerSocket()
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
Server::safeRead(int fd, string& request)
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
Server::safeWrite(int fd, const string& response)
{
    size_t len = response.length()+1;
    char buf[len];
    memcpy(buf, response.c_str(), len);
    buf[len-1] = 0;

	ssize_t ret = _socket.write(fd, buf, len);
	if (_socket.lastErr() == -1)
	{
		// TODO: log
        cout << "false" << endl;
	}

	return ret;
}

bool
Server::epollCtl(ServerContext* ctx, int op, uint32_t events)
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
Server::addClient(int clientFd)
{
    ServerContext* ctx = new ServerContext;
    ctx->_fd = clientFd;
    ref(ctx);
    cout << "block" << SocketOption::setNoBlock(clientFd);
    //cout << "delay" << SocketOption::setNoDelay(clientFd);
    
    if (!addReadEvent(ctx))
    {
        closeClient();
    }
}

void
Server::closeClient(ServerContext* ctx)
{
	assert(ctx != NULL);

	close(ctx->_fd);
	unref(ctx);

	assert(ctx->_refTimes == 0);
	ctx = NULL;
}
bool 
Server::addReadEvent(ServerContext* ctx, bool modify)
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
Server::addWriteEvent(ServerContext* ctx, bool modify)
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
Server::delEvent(ServerContext* ctx)
{
    if (!epollCtl(ctx, EPOLL_CTL_DEL, 0))
    {
        //TODO
        return false;
    }

    return true;
}

void
Server::deal()
{
	while (true)
	{
		ServerContext* ctx = fetchUnsolve();

		ctx->clear();
		string request = "";
		ssize_t rdbytes = safeRead(ctx->_fd, request);

		if (rdbytes == 0)
		{
            cout << 2 << endl;
            closeClient(ctx);
            continue;
		}

		assert(_handler != NULL);
		string response = "";

		try
		{
			response = _handler->handle(request);
            cout << request << endl;
		}
		catch (exception& e)
		{
            cout << e.what() << endl;
			closeClient(ctx);
            cout << 11 << endl;
			// TODO:
		}

		ctx->_request = request;
		ctx->_response = response;

        if (!addWriteEvent(ctx))
        {
            closeClient(ctx);
            ctx = NULL;
        }
        else
        {
            ref(ctx);
        }
	}
}

void
Server::handleEvent(epoll_event& event)
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
Server::handleReadEvent(ServerContext* ctx)
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
Server::handleWriteEvent(ServerContext* ctx)
{
    assert(ctx != NULL);

    ssize_t wtbytes = safeWrite(ctx->_fd, ctx->_response);
    if (wtbytes == -1)
    {
        // TODO
        return false;
    }

    cout << "response: " << ctx->_response.size() << endl;
    cout << "write:  : " << wtbytes << endl;
    
    // TODO: return
    if (!addReadEvent(ctx, true))
    {
        cout << 3 << endl;
        return false;
    }

    ref(ctx);

    return true;
}

void
Server::ref(ServerContext* ctx)
{
	assert(ctx != NULL);
	ctx->_refTimes += 1;
}

void
Server::unref(ServerContext* ctx)
{
	assert(ctx != NULL);
	ctx->_refTimes -= 1;

	if (ctx->_refTimes == 0)
		delete ctx;
}

void
Server::addUnsolve(ServerContext* ctx)
{
	assert(ctx != NULL);
	ref(ctx);
	
	unique_lock<mutex> lock(_mtxQueue);
	_needSolving.push(ctx);
    _cond.notify_all();
}

ServerContext*
Server::fetchUnsolve()
{
	unique_lock<mutex> lock(_mtxQueue);

	while (_needSolving.empty())
	{
		_cond.wait(lock);
	}

	ServerContext* ctx = _needSolving.front();
	_needSolving.pop();

	return ctx;
}
