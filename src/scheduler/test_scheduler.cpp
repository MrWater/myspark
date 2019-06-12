#include <iostream>

#include "task/TestTask.h"
#include "task/TestTaskGraph.h"
#include "SingleScheduler.cpp"

using namespace std;
using namespace ns_scheduler;
using namespace ns_task;


int main()
{
    TestTask task1;
    TestTask task2;
    TestTask task3;
    TestTask task4;

    task2.addRelyTask(&task1);
    task2.addRelyTask(&task3);
    task3.addRelyTask(&task1);
    task4.addRelyTask(&task2);
    task4.addRelyTask(&task3);

    TestTaskGraph graph;
    graph.addTask(&task1);
    graph.addTask(&task2);
    graph.addTask(&task3);
    graph.addTask(&task4);
    
    cout << "task1：" << task1.id() << endl;
    cout << "task2：" << task2.id() << endl;
    cout << "task3：" << task3.id() << endl;
    cout << "task4：" << task4.id() << endl;

    SingleScheduler scheduler;
    scheduler.receive(&graph);
    scheduler.schedule();

    return 0;
}
