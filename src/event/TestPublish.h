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

    virtual void notify()
    {
        ns_container::SafeList<SubscribeBase*>::iterator iter = _subscribers.begin();

        for (; iter != _subscribers.end(); ++iter)
            (*iter)->respond();
    }
};

};

#endif
