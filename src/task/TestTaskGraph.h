#ifndef __TEST_TASKGRAPH_H__
#define __TEST_TASKGRAPH_H__

#include <vector>

#include "TaskGraphBase.h"


namespace ns_task
{

class TestTaskGraph;

class TestTaskGraphIterator: public Iterator<TaskBase*>
{
public:
    ~TestTaskGraphIterator() {}

private:
    TestTaskGraphIterator() {}
    friend class TestTaskGraph;
};

class TestTaskGraph : public TaskGraphBase<TestTaskGraphIterator>
{
public:
    TestTaskGraph() {}
    ~TestTaskGraph() {}

    virtual void addTask(TaskBase* task) { _allTask.push_back(task); }
    virtual size_t size() const { return _allTask.size(); }

    virtual TestTaskGraphIterator begin()
    {
        TestTaskGraphIterator
    }

private:
    std::vector<TaskBase*> _allTask;
};

}

#endif
