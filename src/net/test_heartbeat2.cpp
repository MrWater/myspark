#include <iostream>
#include "Heartbeat.h"

using namespace std;
using namespace ns_net;


int main()
{
    Heartbeat beat("hello", "127.0.0.1", 8090);
    bool ret = beat.sendto("127.0.0.1", 8080);
    cout << ret << endl;
    ret = beat.sendto("127.0.0.1", 8080);
    cout << ret << endl;

    return 0;
}

