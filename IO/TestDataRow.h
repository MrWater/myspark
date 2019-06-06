#ifndef __TEST_DATAROW_H__
#define __TEST_DATAROW_H__


#include  "DataRowBase.h"


namespace ns_io
{

class TestDataRow : public DataRowBase
{
public:
    TestDataRow() : key(0), value(0) {}
    TestDataRow(int k, int v) : key(k), value(v) {}
    ~TestDataRow() {}

public:
    int key;
    int value;
};
}

#endif
