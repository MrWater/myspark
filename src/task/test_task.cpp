#include <iostream>
#include <gtest/gtest.h>

#include "TestTask.h"
#include "TestTaskGraph.h"

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
    pTask->addRelyTask(&task3);
    pTask->run();

    TestTaskGraph graph;
    graph.addTask(&task1);
    graph.addTask(&task2);
    graph.addTask(&task3);

    cout << "task1：" << task1.id() << endl;
    cout << "task2：" << task2.id() << endl;
    cout << "task3：" << task3.id() << endl;

    cout << graph.hasNext() << endl;
    cout << graph.size() << endl;

    return 0;
}
