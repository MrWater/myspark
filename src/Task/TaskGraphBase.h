#ifndef __TASKGRAPH_BASE_H__
#define __TASKGRAPH_BASE_H__

#include "TaskBase.h"
#include "Common/IteratorBase.h"


namespace ns_task
{

class TaskGraphBase : public IteratorBase<TaskBase*>
{
public:
    TaskGraphBase() {}
    virtual ~TaskGraphBase() {}

    virtual void addTask(TaskBase* task) = 0;
    virtual bool hasNext() const = 0;
    virtual TaskBase* next() = 0;
    virtual size_t size() const = 0;
};

}

#endif
