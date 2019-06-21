#ifndef __NOT_SEQUENCE_ITERATOR_H__
#define __NOT_SEQUENCE_ITERATOR_H__


#include "Iterator.h"


template<typename TEle, typename TStlIterator>
class NotSequenceIterator : public Iterator<TEle>
{
public:
    virtual ~NotSequenceIterator() {}

protected:
    NotSequenceIterator() {}
    
    virtual void next() { ++_iter; this->_current = &(*_iter); }
    virtual void prev() { --_iter; this->_current = &(*_iter); }

protected:
    TStlIterator _iter;
};

#endif
