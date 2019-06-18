#ifndef __SAFE_VECTOR_H__
#define __SAFE_VECTOR_H__


#include <vector>

#include "thread/Lock.h"
#include "thread/AutoLock.h"
#include "common/Iterator.h"
#include "common/Iterateable.h"


namespace ns_container
{

template<typename TEle>
class SafeVectorIterator;

template<typename TEle>
class SafeVector : public Iterateable<TEle, SafeVectorIterator<TEle>>
{
public:
    SafeVector() {}
    ~SafeVector() {}

    void add(TEle ele)
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::WRITE);
        _vector.push_back(ele);
    }

    void extend(SafeVector<TEle> lst)
    {

    }

    void erase(const TEle& ele)
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::WRITE);
        typename std::vector<TEle>::iterator iter = _vector.begin();

        for (; iter != _vector.end(); ++iter)
        {
            if (*iter == ele)
            {
                _vector.erase(iter);
                return;
            }
        }
    }

    bool find(const TEle& ele, TEle* ret)
    {
        // if (ret == NULL) 

        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::READ);
        typename std::vector<TEle>::iterator iter = _vector.begin();
        
        for (; iter != _vector.end(); ++iter)
        {
            if (*iter == ele)
            {
                *ret = *iter;
                return true;
            }
        }
        
        return false;
    }

    bool empty()
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::READ);
        return _vector.empty();
    }

    size_t size()
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::READ);
        return _vector.size();
    }

    virtual SafeVectorIterator<TEle> begin()
    {
        SafeVectorIterator<TEle> iter;
        iter._current = &(*_vector.begin());
        return iter;
    }

    virtual SafeVectorIterator<TEle> end()
    {
        SafeVectorIterator<TEle> iter;
        iter._current = &(*_vector.end());
        return iter;
    }
    
private:
    std::vector<TEle> _vector;
    ns_thread::RWLock _rwlock;
};

template<typename TEle>
class SafeVectorIterator : public Iterator<TEle>
{
public:
    ~SafeVectorIterator() {}

private:
    SafeVectorIterator() {}
    friend class SafeVector<TEle>;
};

}

#endif
