#include <iostream>
#include <string>

#include "XString.h"

using namespace std;


int main()
{
    string src = "#a#b###a##";
    string sep = "#";

    vector<string> ret = XString::split(src, sep);
    vector<string>::iterator iter = ret.begin();

    cout << src << endl;
    for (; iter != ret.end(); ++iter)
        cout << "=" << *iter << "=" << endl;

    return 0;
}
