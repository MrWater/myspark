#include <iostream>

#include "UUID.h"

using namespace std;


int main()
{
    UUID uuid;
    string s = static_cast<string>(uuid);
    cout << s << endl;

    return 0;
}
