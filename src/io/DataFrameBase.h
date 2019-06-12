#ifndef __DATAFRAME_BASE_H__
#define __DATAFRAME_BASE_H__


#include <vector>

#include "DataRowBase.h"
#include "common/IteratorBase.h"
#include "exception/IOException.h"


namespace ns_io
{

class DataFrameBase : public IteratorBase<DataRowBase*>
{
public:
    DataFrameBase() {}
    virtual ~DataFrameBase() {}

    virtual void add(DataRowBase*) = 0;
    virtual DataRowBase& at(size_t idx) throw(ns_exception::IOException) = 0;

    virtual bool hasNext() const = 0;
    virtual DataRowBase* next() = 0;
    virtual size_t size() const = 0;
};

}

#endif
