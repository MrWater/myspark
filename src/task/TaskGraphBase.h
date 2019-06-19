#ifndef __TASKGRAPH_BASE_H__
#define __TASKGRAPH_BASE_H__

#include "TaskBase.h"
#include "common/IteratorBase.h"


namespace ns_task
{

template<typename TIterator>
class TaskGraphBase : public Iterateable<TaskBase*, TIterator>
{
public:
    typedef TIterator iterator;

public:
    virtual ~TaskGraphBase() {}

    virtual void addTask(TaskBase* task) = 0;
    virtual size_t size() const = 0;
    virtual TIterator begin() = 0;
    virtual TIterator end() = 0;

protected:
    TaskGraphBase() {}
};

}

#endif
