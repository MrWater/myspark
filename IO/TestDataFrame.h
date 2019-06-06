#ifndef __TEST_DATAFRAME_H__
#define __TEST_DATAFRAME_H__


#include "DataFrameBase.h"
#include "DataRowBase.h"

namespace ns_io
{

class TestDataFrame : public DataFrameBase
{
public:
    TestDataFrame() {}
    ~TestDataFrame() {}

    virtual size_t length() const { return _data.size(); }
    virtual void add(DataRowBase* row) { _data.push_back(row); } 
    virtual DataRowBase& at(size_t idx) throw(ns_exception::IOException)
    {
        if (idx < 0 || idx > length())
            throw ns_exception::IOException("index overflow");

        return *(_data[idx]);
    }
};

}

#endif
