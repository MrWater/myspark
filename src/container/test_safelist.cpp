#include <iostream>

#include "SafeList.h"

using namespace std;
using namespace ns_container;


int main()
{
    SafeList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    Iterator<int> iter = list.begin();
    for (; iter != list.end(); ++iter)
        cout << *iter << endl;

    return 0;
}
