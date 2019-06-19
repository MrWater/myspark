#ifndef __SUBSCRIBE_BASE_H__
#define __SUBSCRIBE_BASE_H__


namespace ns_event
{

class SubscribeBase
{
public:
    SubscribeBase() {}

    virtual void respond() = 0;
    
protected:
    virtual ~SubscribeBase() {}
};

}

#endif
