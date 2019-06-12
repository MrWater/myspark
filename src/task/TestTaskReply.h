#ifndef __TESTTASK_REPLY_H__
#define __TESTTASK_REPLY_H__


#include "TaskReplyBase.h"


namespace ns_task
{

struct TestTaskReply : public TaskReplyBase
{
    bool testFlag;
};


}

#endif
