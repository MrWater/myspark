#ifndef __LIST_ITERATOR_H__
#define __LIST_ITERATOR_H__


#include "common/Iterator.h"


namespace ns_container
{

template<typename TEle>
class ListIterator : public Iterator<TEle>
{
public:
    virtual ~ListIterator() {}

protected:
    ListIterator() {}

    virtual void next() { ++_iter; this->_current = &(*_iter); }
    virtual void prev() { --_iter; this->_current = &(*_iter); }

protected:
    typename std::list<TEle>::iterator _iter;
};

}

#endif
