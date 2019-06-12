#ifndef __PUBLIC_BASE_H__
#define __PUBLIC_BASE_H__


#include "SubscribeBase.h"
#include "Common/IteratorBase.h"
#include "container/SafeList.h"


namespace ns_event
{

class PublishBase : public IteratorBase<SubscribeBase*>
{
public:
    PublishBase() {}
    virtual ~PublishBase() {}

    size_t size() { return _subscribers.size(); }
    bool hasNext() { return _iterOffset < _subscribers.size(); }
    SubscribeBase* next() { return _subscribers[_iterOffset++]; }
    void seek(size_t offset=0) { _iterOffset = offset; }

    void attach(SubscribeBase* subscriber) { _subscribers.add(subscriber); }
    void detach(SubscribeBase* subscriber) 
    {
        std::list<SubscribeBase*>::iterator iter = _subscribers.find(subscriber);
        if (iter != _subscribers.end())
            _subscribers.
    }

    virtual notify() const = 0;

private:
    ns_container::SafeList<SubscribeBase*> _subscribers;
};

}

#endif
