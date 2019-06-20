#include <iostream>
#include "Heartbeat.h"

using namespace std;
using namespace ns_net;


int main()
{
    Heartbeat beat("hello", "127.0.0.1", 8080);
    bool ret = beat.recvfrom(NULL);
    if (ret)
    {
        if (beat.identify())
            cout << "y" << endl;
        else
            cout << "n" << endl;
    }

    cout << ret << endl;
    ret = beat.recvfrom(NULL);
    if (ret)
    {
        if (beat.identify())
            cout << "y" << endl;
        else
            cout << "n" << endl;
    }

    cout << ret << endl;

    return 0;
}

