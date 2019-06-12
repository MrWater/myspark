#ifndef __TASK_REPLY_H__
#define __TASK_REPLY_H__


#include <string>

#include "io/DataFrameBase.h"


namespace ns_task
{

struct TaskReplyBase
{
    bool ok;
    std::string msg;
    ns_io::DataFrameBase* data;
};

}

#endif
