#ifndef __ITASK_H__
#define __ITASK_H__


#include "TaskStatus.h"

namespace ns_task
{

class ITask
{
public:
    virtual TaskStatus run() = 0;
};

}

#endif
