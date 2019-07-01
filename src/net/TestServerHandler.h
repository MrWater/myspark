#ifndef __TEST_SERVER_HANDLER_H__
#define __TEST_SERVER_HANDLER_H__


#include <fstream>
#include <sstream>
#include <iostream>

#include "ServerHandlerBase.h"

using namespace std;

namespace ns_net
{

class TestServerHandler : public ServerHandlerBase
{
public:
    TestServerHandler()
        : ServerHandlerBase()
    {
    }

    ~TestServerHandler() {}

    virtual std::string handle(const std::string& request)
    {
        ifstream fs("test.txt");
        ostringstream oss;
        string line = "";

        while (getline(fs, line))
        {
            oss << line << "\n";
        }

        return oss.str();
    }
};

}


#endif
