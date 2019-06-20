#ifndef __TEST_DATAFRAME_H__
#define __TEST_DATAFRAME_H__


#include "DataFrameBase.h"

namespace ns_io
{

class TestDataFrame;

template<typename TEle>
class TestDataFrameIterator : public Iterator<TEle>
{
public:
    ~TestDataFrameIterator() {}

private:
    TestDataFrameIterator() {}
    friend class TestDataFrame;
};


class TestDataFrame : public DataFrameBase<TestDataFrameIterator<DataRowBase*>>
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

    virtual size_t size() const { return _data.size(); }
    
    virtual iterator begin()
    {
        iterator iter;
        iter._current = &(*_data.begin());
        return iter;
    }    

    virtual iterator end()
    {
        iterator iter;
        iter._current = &(*_data.end());
        return iter;
    }

private:
    std::vector<DataRowBase*> _data;   
};

}

#endif
