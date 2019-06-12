#include <iostream>

#include "SafeList.h"

using namespace std;
using namespace ns_container;


int main()
{
    SafeList<int> list;
    list.add(1);
    list.add(3);

    int a;
    cout << list.find(1, &a) << endl;
    cout << a << endl;

    cout << list.size() << endl;
    list.erase(1);
    cout << list.size() << endl;

    return 0;
}
