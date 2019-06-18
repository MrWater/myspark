#include <iostream>

#include "TestDataFrame.h"
#include "TestDataRow.h"

using namespace std;
using namespace ns_io;


int main()
{
    TestDataRow row(1, 2);
    cout << row.key << endl;
    cout << row.value << endl;

    TestDataFrame frame;
    frame.add(dynamic_cast<DataRowBase*>(&row));
    frame.add(dynamic_cast<DataRowBase*>(&row));
    frame.add(dynamic_cast<DataRowBase*>(&row));
    frame.add(dynamic_cast<DataRowBase*>(&row));

    cout << frame.size() << endl;
    TestDataRow& temp = static_cast<TestDataRow&>(frame.at(0));
    cout << temp.key << endl;
    temp.key = 2;
    cout << temp.key << endl;

    try
    {
        frame.at(10);
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }

    TestDataFrame::iterator iter = frame.begin();
    for(; iter != frame.end(); ++iter)
    {
        cout << (dynamic_cast<TestDataRow*>(*iter))->key << endl;
    }


    return 0;
};
