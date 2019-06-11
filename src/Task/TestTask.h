#ifndef __TEST_TASK_H__
#define __TEST_TASK_H__


#include <iostream>
#include <unistd.h>

#include "TaskBase.h"


namespace ns_task
{

class TestTask : public TaskBase
{
public:
    TestTask() : TaskBase() {}
    virtual ~TestTask() {}

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
            std::cout << "TestTask run" << std::endl;
        else
            std::cout << "TestTask cannot run" << std::endl;

        sleep(1);
        _status = TaskStatus::SUCCESSFUL;
    } 
};

}

#endif