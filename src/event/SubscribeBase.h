#ifndef __SUBSCRIBE_BASE_H__
#define __SUBSCRIBE_BASE_H__


namespace ns_event
{

class SubscribeBase
{
public:
    SubscribeBase() {}
    virtual ~SubscribeBase() {}

    virtual void respond() = 0;
};

}

#endif
