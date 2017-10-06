#include <iostream>
#include "AList.h"
#include "LList.h"
typedef double type;
using namespace std;
int nPoint(AList<type> A,LList<type> L)
{
    int n=0;
    while(sizeof(A)>sizeof(L))
    {
        A.append(1);
        L.append(1);
        n++;
    }
    return n;
}
int main()
{
    AList<type> A;
    A.clear();
    LList<type> L;
    L.clear();
    int n=nPoint(A,L);
    cout<<"the break-even-point of type int is "<<n<<endl;
    return 0;
}
