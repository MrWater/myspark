#ifndef __ITERATOR_BASE_H__
#define __ITERATOR_BASE_H__


template<typename TEle>
class IteratorBase
{
public:
    IteratorBase() {}
    virtual ~IteratorBase() {}

    virtual IteratorBase& operator++() = 0;
    virtual IteratorBase operator++(int) = 0;
    virtual IteratorBase& operator--() = 0;
    virtual IteratorBase operator--(int) = 0;
    virtual TEle& operator*() = 0;
    virtual TEle* operator->() = 0;
    virtual bool operator==(const IteratorBase& iter) const = 0;
    virtual bool operator!=(const IteratorBase& iter) const = 0;
    virtual bool operator<(const IteratorBase& iter) const = 0;
};

#endif

