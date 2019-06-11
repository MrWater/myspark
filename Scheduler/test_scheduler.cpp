#include <iostream>

#include "Task/TestTask.h"
#include "Task/TestTaskGraph.h"
#include "SingleScheduler.cpp"

using namespace std;
using namespace ns_scheduler;
using namespace ns_task;


int main()
{
    TestTask task1;
    TestTask task2;
    TestTask task3;

    task3.addRelyTask(&task1);
    task3.addRelyTask(&task2);

    TestTaskGraph graph;
    graph.addTask(&task1);
    graph.addTask(&task2);
    graph.addTask(&task3);

    SingleScheduler scheduler;
    scheduler.receive(&graph);
    scheduler.schedule();

    return 0;
}
