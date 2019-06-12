#ifndef __TEST_DATAFRAME_H__
#define __TEST_DATAFRAME_H__


#include "DataFrameBase.h"

namespace ns_io
{

class TestDataFrame : public DataFrameBase
{
public:
    TestDataFrame() {}
    virtual ~TestDataFrame() {}

    virtual void add(DataRowBase* row) { _data.push_back(row); } 
    virtual DataRowBase& at(size_t idx) throw(ns_exception::IOException)
    {
        if (idx < 0 || idx > size())
            throw ns_exception::IOException("index overflow");

        return *(_data[idx]);
    }

    virtual bool hasNext() const { return _iterOffset < _data.size(); }
    virtual size_t size() const { return _data.size(); }
    virtual DataRowBase* next()
    {
        DataRowBase* row = _data[_iterOffset];
        ++_iterOffset;

        return row;
    }
    
private:
    std::vector<DataRowBase*> _data;   
};

}

#endif
