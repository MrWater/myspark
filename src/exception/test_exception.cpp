#include <iostream>
#include <map>
#include <stdint.h>

#include "IOException.h"
#include "ExceptionCode.h"

using namespace std;
using namespace ns_exception;

//map<uint32_t, string> ExceptionCodeMap { {1, "1"}};


int main()
{
    try
    {
        throw IOException("test");
    }
    catch(IOException& e)
    {
        cout << e.what() << endl;
    }

    cout << ExceptionCodeMap[0] << endl;

    return 0;
}
