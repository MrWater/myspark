#ifndef __SAFE_LIST_H__
#define __SAFE_LIST_H__


#include <list>

#include "thread/Lock.h"
#include "thread/AutoLock.h"
#include "common/IteratorBase.h"


namespace ns_container
{

template<typename TEle>
class SafeList// : public IteratorBase<TEle>
{
public:
    SafeList() {}
    ~SafeList() {}

    void add(TEle ele)
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::WRITE);
        _list.push_back(ele);
    }

    void extend(SafeList<TEle> lst)
    {

    }

    void erase(const TEle& ele)
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::WRITE);
        typename std::list<TEle>::iterator iter = _list.begin();

        for (; iter != _list.end(); ++iter)
        {
            if (*iter == ele)
            {
                _list.erase(iter);
                return;
            }
        }
    }

    bool find(const TEle& ele, TEle* ret)
    {
        // if (ret == NULL) 

        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::READ);
        typename std::list<TEle>::iterator iter = _list.begin();
        
        for (; iter != _list.end(); ++iter)
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
        return _list.empty();
    }

    size_t size()
    {
        ns_thread::AutoLock(&_rwlock, ns_thread::RWLock::READ);
        return _list.size();
    }
    
private:
    std::list<TEle> _list;
    ns_thread::RWLock _rwlock;
};

}

#endif
