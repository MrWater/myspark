#ifndef __TASK_STATUS_H__
#define __TASK_STATUS_H__


namespace ns_task
{

enum class TaskStatus : short
{
    WAITING,
    READY,
    RUNNING,
    FAILED,
    SUCCESSFUL
};

}

#endif
