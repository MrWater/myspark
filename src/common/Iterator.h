#ifndef __ITERATOR_H__
#define __ITERATOR_H__


#include "IteratorBase.h"

/**
 * brief 
 * 1.not to ensure multi-thread safety temporarily
 * 2.next may need return reference of ele
 * 3....
 *
 * param TEle
 */
template<typename TEle>
class Iterator //: public IteratorBase<TEle>
{
public:
    virtual ~Iterator() {}

    Iterator& operator++()
    {
        next();
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator temp = *this;
        temp._current = this->_current;
        next();
        return temp;
    }

    Iterator& operator--()
    {
        prev();
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator temp = *this;
        temp._current = this->_current;
        prev();
        return temp;
    }

    TEle& operator*() const
    {
        return *_current;
    }

    TEle* operator->() const
    {
        return _current;
    }

    bool operator==(const Iterator& iter) const
    {
        return this->_current == iter._current;
    }
    
    bool operator!=(const Iterator& iter) const
    {
        return this->_current != iter._current;
    }

    bool operator<(const Iterator& iter) const
    {
        return this->_current < iter._current;
    }

protected:
    Iterator() {}

    virtual void next() { ++_current; }
    virtual void prev() { --_current; }

protected:
    TEle* _current;
};

#endif
