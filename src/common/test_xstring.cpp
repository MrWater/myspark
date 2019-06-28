#include <iostream>
#include <string>

#include "XString.h"

using namespace std;


int main()
{
    string src = "";
    char sep = '\t';

    vector<string> ret = XString::split(src, sep);
    vector<string>::iterator iter = ret.begin();

    for (; iter != ret.end(); ++iter)
        cout << "=" << *iter << "=" << endl;

    return 0;
}
