#ifndef __SAFE_LIST_H__
#define __SAFE_LIST_H__


#include <list>

#include "thread/Lock.h"
#include "thread/AutoLock.h"
#include "common/Iterator.h"
#include "common/Iterateable.h"


namespace ns_container
{

template<typename TEle>
class SafeList : public Iterateable<TEle>
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

    virtual Iterator<TEle> begin()
    {  
        SafeListIterator iter;
        iter._iter = _list.begin();
        iter._current = &(*iter._iter);
        return static_cast<Iterator<TEle>>(iter);
    }

    virtual const Iterator<TEle> end()
    {
        SafeListIterator iter;
        iter._iter = _list.end();
        iter._current = &(*iter._iter);
        return static_cast<Iterator<TEle>>(iter);
    }
    
private:
    std::list<TEle> _list;
    ns_thread::RWLock _rwlock;

private:
    class SafeListIterator : public Iterator<TEle>
    {
    protected:
        SafeListIterator() {}
        ~SafeListIterator() {}

        virtual void next() { ++_iter; _current = &(*_iter); }
        virtual void prev() { --_iter; _current = &(*_iter); }

    private:
        friend class SafeList;
        typename std::list<TEle>::iterator _iter;
    };

};


}

#endif
