#ifndef __TEST_TASK_H__
#define __TEST_TASK_H__


#include <iostream>
#include <unistd.h>

#include "TaskBase.h"
#include "TestTaskReply.h"
#include "io/TestDataRow.h"
#include "io/TestDataFrame.h"


namespace ns_task
{

class TestTask : public TaskBase
{
public:
    TestTask() : TaskBase() {}
    virtual ~TestTask() 
    {
        // delete reply when delete task?
        // TODO: better solution for destruction?
        while(_frame.hasNext())
        {
            delete _frame.next();
        }

        delete _reply;
        std::cout << "~TestTask" << std::endl;
    }

    virtual TaskStatus run() 
    {
        auto iter = _relyTasks.begin();
        bool flag = true;

        for (; iter != _relyTasks.end(); ++iter)
        {
            if ((*iter)->status() == TaskStatus::WAITING)
            {
                flag = false;
                break;
            }
        }

        if (flag)
            std::cout << id() << " run" << std::endl;
        else
            std::cout << "TestTask cannot run" << std::endl;

        sleep(5);
        _status = TaskStatus::SUCCESSFUL;

        ns_io::TestDataRow* row = new (std::nothrow) ns_io::TestDataRow;
        row->key = 1;
        row->value = 2;
        _frame.add(row);

        TestTaskReply* reply = new (std::nothrow) TestTaskReply;
        reply->data = &_frame;
        reply->testFlag = true;
        _reply = dynamic_cast<TaskReplyBase*>(reply);
    }

private:
    ns_io::TestDataFrame _frame;
};

}

#endif
