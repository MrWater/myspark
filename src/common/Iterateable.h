#ifndef __ITERATEABLE_H__
#define __ITERATEABLE_H__


#include "Iterator.h"


template<typename TEle>
class Iterateable
{
public:
    Iterateable() {}
    ~Iterateable() {}

    virtual Iterator<TEle> begin() = 0;
    virtual const Iterator<TEle> end() = 0;
};

#endif
