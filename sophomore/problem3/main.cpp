#include <iostream>
#include "AList.h"
#include "LList.h"
typedef int type;
using namespace std;
AList<type> merge(AList<type> a, AList<type> b)
{
    AList<type> m;
    a.moveToEnd();
    b.moveToEnd();
    while(1)
    {
            if(a.getValue()<b.getValue())
            {
                m.append(b.getValue());
                cout<<b.getValue()<<" ";
                b.prev();
            }
            if(a.getValue()==b.getValue())
            {
                m.append(a.getValue());
                cout<<a.getValue()<<" ";
                b.prev();
                a.prev();
            }
            if(a.getValue()>b.getValue())
            {
                m.append(a.getValue());
                a.prev();
            }
    }
    return m;
}
int main()
{
    AList<type> a,b;
    for(int i=0;i<4;i++)
        a.append(2*i);
    for(int i=0;i<4;i++)
        b.append(2*i+1);
    merge(a,b);
    return 0;
}
