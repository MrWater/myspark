#ifndef __TEST_SUBSCRIBE_H__
#define __TEST_SUBSCRIBE_H__


#include <iostream>

#include  "SubscribeBase.h"


namespace ns_event
{

class TestSubscribe : public SubscribeBase
{
public:
    TestSubscribe() {}
    virtual ~TestSubscribe() {}

    virtual void respond()
    {
        std::cout << "test" << std::endl;
    }
};

}

#endif
