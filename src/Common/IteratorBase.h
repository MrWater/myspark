#ifndef __ITERATOR_BASE_H__
#define __ITERATOR_BASE_H__


template<typename TEle>
class IteratorBase
{
public:
    IteratorBase() : _iterOffset(0) {}
    ~IteratorBase() {}

    virtual bool hasNext() const = 0;
    virtual TEle next() = 0;
    virtual size_t size() const = 0;
    virtual void reset() { _iterOffset = 0; }

protected:
    size_t _iterOffset;
};

#endif
