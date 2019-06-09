#include <iostream>

#include "TestDataRow.h"
#include "LocalFileIO.h"

using namespace std;
using namespace ns_io;


int main()
{
    LocalFileIO file("test.txt");
    if (!file.open(FileIOTypes::WRITE))
    {
        cout << "open error" << endl;
        return 0;
    }
   
    TestDataRow row;
    row.key = 1;
    row.value = 1;
    file.write((DataRowBase)row, sizeof(row));
    file.close();

    return 0;
}
