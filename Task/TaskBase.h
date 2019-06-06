#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__


#include <list>
#include <stdint.h>

#include "ITask.h"

namespace ns_task
{

class TaskBase : public ITask
{
public:
    TaskBase() : _status(TaskStatus::NONE) {}
    virtual ~TaskBase() {}

    TaskStatus status() { return _status; }
    uint32_t relyNum() { return _relyTasks.size(); }
    void addRelyTask(TaskBase* task) { _relyTasks.push_back(task); }

public:
    virtual TaskStatus run() = 0;

protected:
    TaskStatus _status;
    std::list<TaskBase*> _relyTasks;    
};

}

#endif
