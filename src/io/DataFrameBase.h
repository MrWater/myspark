#ifndef __DATAFRAME_BASE_H__
#define __DATAFRAME_BASE_H__


#include <vector>

#include "DataRowBase.h"
#include "common/Iterator.h"
#include "common/Iterateable.h"
#include "exception/IOException.h"


namespace ns_io
{

template<typename TIterator>
class DataFrameBase : public Iterateable<DataRowBase*, TIterator>
{
public:
    virtual ~DataFrameBase() {}

    virtual void add(DataRowBase*) = 0;
    virtual DataRowBase& at(size_t idx) throw(ns_exception::IOException) = 0;

    virtual size_t size() const = 0;
    virtual TIterator begin() = 0;
    virtual TIterator end() = 0;
    
protected:
    DataFrameBase() {}
};

}

#endif
