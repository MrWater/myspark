#include <iostream>

#include "SafeVector.h"

using namespace std;
using namespace ns_container;


int main()
{
    SafeVector<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    SafeVector<int>::iterator iter = list.begin();

    for (; iter != list.end(); ++iter)
        cout << *iter << endl;

    return 0;
}
