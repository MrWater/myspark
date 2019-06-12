#ifndef __SINGLE_SCHEDULER_H__
#define __SINGLE_SCHEDULER_H__


#include <unistd.h>

#include "SchedulerBase.h"
#include "task/TaskGraphBase.h"


namespace ns_scheduler
{

class SingleScheduler : public SchedulerBase
{
public:
    SingleScheduler() : SchedulerBase() {}
    virtual ~SingleScheduler() {}

    virtual void receive(ns_task::TaskGraphBase* graph) { _graph = graph; }

    virtual void schedule()
    {
        bool run_flag = false;
        ns_task::TaskBase* temp = NULL;

        while (1)
        {
            run_flag = false;
            _graph->seek();

            while (_graph->hasNext())
            {
                temp = _graph->next();
                temp->updateStatus();

                if (ns_task::TaskStatus::READY == temp->status())
                {
                    temp->run();
                    run_flag = true;
                }
            }

            if (!run_flag)
                break;
        }
    }

private:
    ns_task::TaskGraphBase* _graph;
};

}

#endif
