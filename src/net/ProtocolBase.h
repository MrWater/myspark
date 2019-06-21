#ifndef __PROTOCOL_BASE_H__
#define __PROTOCOL_BASE_H__


#include <iostream>
#include <string>


namespace ns_net
{

class ProtocolBase
{
public:
    virtual ~ProtocolBase() {}
    
    virtual std::string serialize() const = 0;
    virtual void deserialize(std::string src) = 0;

protected:
    ProtocolBase() {}
};

}

#endif
