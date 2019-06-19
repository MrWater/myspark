#ifndef __SCHEDULER_BASE_H__
#define __SCHEDULER_BASE_H__


#include "task/TaskGraphBase.h"


namespace ns_scheduler
{

class SchedulerBase
{
public:
    virtual void receive(ns_task::TaskGraphBase* graph) = 0;
    virtual void schedule() = 0;
    virtual void watch() {}

protected:
    SchedulerBase() {}
    virtual ~SchedulerBase() {}
};

}

#endif
