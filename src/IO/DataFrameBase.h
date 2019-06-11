#ifndef __DATAFRAME_BASE_H__
#define __DATAFRAME_BASE_H__


#include <vector>

#include "DataRowBase.h"
#include "Exception/IOException.h"


namespace ns_io
{

class DataFrameBase
{
public:
    DataFrameBase() {}
    virtual ~DataFrameBase() {}

    virtual size_t length() const = 0;
    virtual void add(DataRowBase*) = 0;
    virtual DataRowBase& at(size_t idx) throw(ns_exception::IOException) = 0;

protected:
    std::vector<DataRowBase*> _data;   
};

}

#endif