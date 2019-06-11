#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__


#include <list>
#include <stdint.h>

#include "TaskStatus.h"
#include "Common/UUID.h"


namespace ns_task
{

class TaskBase
{
public:
    TaskBase() : _status(TaskStatus::READY), id(UUID()) {}
    virtual ~TaskBase() {}

    TaskStatus status() { return _status; }
    size_t relyNum() { return _relyTasks.size(); }

    void addRelyTask(TaskBase* task) 
    { 
        _relyTasks.push_back(task); 
        _status = TaskStatus::WAITING;
    }
    
    size_t waitNum() const
    {
        size_t cnt = 0;
        std::list<TaskBase*>::const_iterator iter = _relyTasks.begin();

        for(; iter != _relyTasks.end(); ++iter)
        {
            if ((*iter)->status() != TaskStatus::SUCCESSFUL)
                ++cnt;
        }

        return cnt;
    }

    void updateStatus()
    {
        if (waitNum() == 0)
            _status = TaskStatus::READY;
        else
            _status = TaskStatus::WAITING;
    }
    
public:
    virtual TaskStatus run() = 0;

public:
    const std::string id;

protected:
    TaskStatus _status;
    std::list<TaskBase*> _relyTasks;
};

}

#endif
