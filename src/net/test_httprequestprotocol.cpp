#include <iostream>
#include <string>
#include "HttpRequestProtocol.h"

using namespace std;
using namespace ns_net;


int main()
{
    string s = "GET /?a=321312412414124 HTTP/1.1\nUser-Agent: curl/7.29.0\nHost: 127.0.0.1:8080\nAccept: */*\n\nfasdfasfasf";
    HttpRequestProtocol protocol;
    protocol.deserialize(s);
    cout << protocol.serialize() << endl;

    return 0;
}
