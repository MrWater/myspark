#include <iostream>

#include "TestDataRow.h"
#include "LocalFileIO.h"

using namespace std;
using namespace ns_io;


int main()
{
    LocalFileIO file("./test.txt", sizeof(TestDataRow));
    cout << file.path() << endl; 
    
    if (!file.open(FileIOTypes::READ_WRITE))
    {
        cout << "open error" << endl;
        TestDataRow row;
        row.key = 1;
        row.value = 1;
        file.write((DataRowBase*)&row);
        file.seek(0);
        
        TestDataRow row2;
        file.read((DataRowBase*)&row2);
        cout << row2.key << " " << row2.value << endl;

        file.close();
        return 0;
    }
   
    TestDataRow row;
    row.key = 1;
    row.value = 1;
    file.write((DataRowBase*)&row);
    row.key = 100;
    row.value = 100;
    file.write((DataRowBase*)&row);
    file.seek(0);

    TestDataRow row2;
    cout << file.read((DataRowBase*)&row2) << endl;
    cout << row2.key << " " << row2.value << endl;
    cout << file.read((DataRowBase*)&row2) << endl;
    cout << row2.key << " " << row2.value << endl;
    cout << file.read((DataRowBase*)&row2) << endl;

    file.close();

    return 0;
}
