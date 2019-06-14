#ifndef __PUBLIC_BASE_H__
#define __PUBLIC_BASE_H__


#include "SubscribeBase.h"
#include "common/Iterateable.h"
#include "container/SafeList.h"


namespace ns_event
{

class PublishBase
{
public:
    PublishBase() {}
    virtual ~PublishBase() {}

    void attach(SubscribeBase* subscriber) { _subscribers.add(subscriber); }
    void detach(SubscribeBase* subscriber) { _subscribers.erase(subscriber); }

    virtual void notify() = 0;

protected:
    ns_container::SafeList<SubscribeBase*> _subscribers;
};

}

#endif
