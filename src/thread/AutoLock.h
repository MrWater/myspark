#ifndef __AUTO_LOCK_H__
#define __AUTO_LOCK_H__

#include "Lock.h"


namespace ns_thread
{

class AutoLock
{
public:
    AutoLock(ILock* lock, ILock::Types type)
    {
        assert(lock != NULL);
        
        _lock = lock;
        _lock->Lock(type);
    }

    ~AutoLock() 
    {
        _lock->UnLock();
    }

private:
    AutoLock(const AutoLock&); // = delete
    AutoLock& operator=(const AutoLock&);

private:
    ILock* _lock;
};

}

#endif
