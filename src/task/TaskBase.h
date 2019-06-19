#ifndef __TASK_BASE_H__
#define __TASK_BASE_H__


#include <list>
#include <functional>
#include <stdint.h>

#include "TaskStatus.h"
#include "common/UUID.h"
#include "TaskReplyBase.h"


namespace ns_task
{

class TaskBase
{
public:
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
        // TODO:FAILED
        if (_status == TaskStatus::RUNNING ||
            _status == TaskStatus::SUCCESSFUL)
            return;

        if (waitNum() == 0)
            _status = TaskStatus::READY;
        else
            _status = TaskStatus::WAITING;
    }

    TaskReplyBase reply() const { return *_reply; }
    const std::string id() const { return _id; }
    
public:
    virtual TaskStatus run() = 0;
    virtual void notify() {}

protected:
    TaskBase() 
        : _status(TaskStatus::READY), 
        _id(UUID()),
        _reply(NULL)
    {
    }

protected:
    TaskStatus _status;
    std::list<TaskBase*> _relyTasks;
    TaskReplyBase* _reply;

private:
    const std::string _id;
};

}

#endif
