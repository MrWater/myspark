#ifndef __TEST_PUBLISH_H__
#define __TEST_PUBLISH_H__


#include  "PublishBase.h"


namespace ns_event
{

class TestPublish : public PublishBase
{
public:
    TestPublish() {}
    virtual ~TestPublish() {}

    virtual notify() const
    {
    }
};

};


#endif
