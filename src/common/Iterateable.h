#ifndef __ITERATEABLE_H__
#define __ITERATEABLE_H__


#include "Iterator.h"


template<typename TEle, typename TIterator>
class Iterateable
{
public:
    typedef TIterator iterator;

public:
    Iterateable() {}
    ~Iterateable() {}

    virtual TIterator begin() = 0;
    virtual TIterator end() = 0;
};

#endif
