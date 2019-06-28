#include <iostream>
#include "ListenSocket.h"
#include "HttpRequestProtocol.h"

using namespace std;
using namespace ns_net;


int main()
{
    ListenSocket socket;
    if (socket.lastErr() == -1)
    {
        cout << "init error" << endl;
        return 0;
    }

    socket.setReuseAddr();
    if (socket.lastErr() == -1)
    {
        cout << "set opt error " << endl;
        return 0;
    }

    socket.bind("127.0.0.1", 8080);
    if (socket.lastErr() == -1)
    {
        cout << "bind error" << endl;
        return 0;
    }
    socket.listen();
    if (socket.lastErr() == -1)
    {
        cout << "listen error" << endl;
        return 0;
    }
    
    int fd = socket.accept(NULL);
    if (socket.lastErr() == -1)
    {
        cout << "accept error" << endl;
        return 0;
    }

    char buf[1024];
    socket.read(fd, buf, 1024);
    if (socket.lastErr() == -1)
    {
        cout << "read error" << endl;
        return 0;
    }
    cout << buf << endl;
    HttpRequestProtocol protocol;
    protocol.deserialize(buf);
    cout << "=============" << endl;
    cout << protocol.serialize() << endl;

    //socket.close();

    return 0;
}
