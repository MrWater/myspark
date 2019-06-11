#ifndef __TEST_TASKGRAPH_H__
#define __TEST_TASKGRAPH_H__

#include <vector>

#include "TaskGraphBase.h"


namespace ns_task
{

class TestTaskGraph : public TaskGraphBase
{
public:
    TestTaskGraph() {}
    ~TestTaskGraph() {}

    virtual void addTask(TaskBase* task) { _allTask.push_back(task); }
    virtual bool hasNext() const { return _iterOffset < _allTask.size(); }
    virtual size_t size() const { return _allTask.size(); }
    
    virtual TaskBase* next() 
    {
        TaskBase* ret = _allTask[_iterOffset];
        ++_iterOffset;

        return ret;
    }

private:
    std::vector<TaskBase*> _allTask;
};

}

#endif
