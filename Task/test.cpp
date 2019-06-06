#include <iostream>
#include <gtest/gtest.h>

#include "TestTask.h"

using namespace std;
using namespace ns_task;


int main()
{
    TestTask task1;
    TestTask task2;
    TestTask task3;
    TestTask task4;

    TaskBase* pTask = &task1;
    pTask->addRelyTask(&task2);
    pTask->run();
    
    return 0;
}
