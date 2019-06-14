#include <iostream>

#include "TestPublish.h"
#include "TestSubscribe.h"

using namespace std;
using namespace ns_event;


int main()
{
    TestPublish p;
    TestSubscribe t;
    p.attach(&t);
    p.attach(&t);

    p.notify();

    return 0;
}
