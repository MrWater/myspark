#ifndef __LOCK_H__
#define __LOCK_H__

#include <pthread.h>
#include <assert.h>


namespace ns_thread
{

class ILock
{
public:
    enum Types { MUTEX, READ, WRITE };

public:
    ILock() {}
    ~ILock() {}

    virtual void Lock(Types type) = 0;
    virtual void UnLock() = 0;
    virtual bool TryLock() = 0;
};


class MutexLock : public ILock
{
public:
    MutexLock() { pthread_mutex_init(&_mtx, NULL); }
    ~MutexLock() { pthread_mutex_destroy(&_mtx); }

    virtual void Lock(Types type) 
    { 
        assert(type == MUTEX);
        pthread_mutex_lock(&_mtx); 
    }

    virtual void UnLock() { pthread_mutex_unlock(&_mtx); }
    virtual bool TryLock() { return pthread_mutex_trylock(&_mtx); }

private:
    MutexLock(const MutexLock&);
    MutexLock& operator=(const MutexLock&);

private:
    pthread_mutex_t _mtx;
};


class RWLock : public ILock
{
public:
    RWLock() { pthread_rwlock_init(&_lock, NULL); }
    ~RWLock() { pthread_rwlock_destroy(&_lock); }

    virtual void Lock(Types type)
    {
        assert(type == WRITE || type == READ);

        switch (type)
        {
        case WRITE:
            pthread_rwlock_wrlock(&_lock);
            break;
        case READ:
            pthread_rwlock_rdlock(&_lock);
            break;
        default:
            // throw expcetion
            break;
        }
    }

    virtual void UnLock() { pthread_rwlock_unlock(&_lock); }
    virtual bool TryLock() { return false; } // throw exception

private:
    RWLock(const RWLock&);
    RWLock& operator=(const RWLock&);

private:
    pthread_rwlock_t _lock;
};

}

#endif
