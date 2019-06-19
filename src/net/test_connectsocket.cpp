#include <iostream>
#include "ConnectSocket.h"

using namespace std;
using namespace ns_net;


int main()
{
    ConnectSocket socket;

    socket.bind("127.0.0.1", 8090);
    socket.connect("127.0.0.1", 8080);

    socket.close();
    return 0;
}
