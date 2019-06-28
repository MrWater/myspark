#include <iostream>

#include "TestServer.h"

using namespace std;
using namespace ns_net;

int main()
{
    TestServer server;
    server.run();

    return 0;
}
