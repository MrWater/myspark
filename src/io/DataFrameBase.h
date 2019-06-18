#ifndef __DATAFRAME_BASE_H__
#define __DATAFRAME_BASE_H__


#include <vector>

#include "DataRowBase.h"
#include "common/Iterator.h"
#include "common/Iterateable.h"
#include "exception/IOException.h"


namespace ns_io
{

template<typename TEle, typename TIterator>
class DataFrameBase : public Iterateable<TEle*, TIterator>
{
public:
    DataFrameBase() {}
    virtual ~DataFrameBase() {}

    virtual void add(TEle*) = 0;
    virtual TEle& at(size_t idx) throw(ns_exception::IOException) = 0;

    virtual size_t size() const = 0;
    virtual TIterator begin() = 0;
    virtual TIterator end() = 0;
};

}

#endif
