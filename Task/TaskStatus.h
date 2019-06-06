#ifndef __TASK_STATUS_H__
#define __TASK_STATUS_H__


namespace ns_task
{

enum class TaskStatus : short
{
    NONE,
    FAILED,
    SUCCESSFUL,
    RUNNING,
    FINISHED
};

}

#endif
