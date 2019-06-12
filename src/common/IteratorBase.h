#ifndef __ITERATOR_BASE_H__
#define __ITERATOR_BASE_H__



/**
 * brief 
 * 1.not to ensure multi-thread safety temporarily
 * 2.next may need return reference of ele
 * 3....
 *
 * param TEle
 */
template<typename TEle>
class IteratorBase
{
public:
    IteratorBase() : _iterOffset(0) {}
    ~IteratorBase() {}

    virtual bool hasNext() const = 0;
    virtual TEle next() = 0;
    virtual size_t size() const = 0;
    virtual void seek(size_t offset=0) { _iterOffset = offset; }

protected:
    size_t _iterOffset;
};

#endif
