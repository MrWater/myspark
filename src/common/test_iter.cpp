#include <iostream>
#include <vector>
#include <list>

#include "Iterator.h"
#include "Iterateable.h"

using namespace std;


class A : public Iterateable<int>
{
private:
    class IteratorA : public Iterator<int>
    {
    public:
    private:
        friend class A;
    };

public:
    A()
    {
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.push_back(4);
        a.push_back(5);
    }

    virtual Iterator<int> begin()
    {
        IteratorA iter;
        iter._current = &a[0];
        return static_cast<Iterator<int>>(iter);
    }

    virtual const Iterator<int> end()
    {
        IteratorA iter;
        iter._current = &(a[a.size()-1]);
        ++iter._current;
        return static_cast<Iterator<int>>(iter);
    }

    vector<int> a;
};


int main()
{
    A a;
    SafeListIterator<int> iter1;
    Iterator<int> iter = a.begin();
    for (; iter!=a.end(); ++iter)
        cout << *iter << endl;


    return 0;
}
