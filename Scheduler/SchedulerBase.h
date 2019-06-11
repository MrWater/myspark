#ifndef __SCHEDULER_BASE_H__
#define __SCHEDULER_BASE_H__


#include "Task/TaskGraphBase.h"


namespace ns_scheduler
{

class SchedulerBase
{
public:
    SchedulerBase() {}
    virtual ~SchedulerBase() {}

    virtual void receive(ns_task::TaskGraphBase* graph) = 0;
    virtual void schedule() = 0;
};

}

#endif
