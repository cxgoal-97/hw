#include <iostream>
#include "AList.h"
#include "LList.h"
typedef int type;
using namespace std;
void intersection(LList<type> a,LList<type> b)
{
    a.moveToStart();
    b.moveToStart();
    while(1){
    	if(a.currPos()==a.length())
		break;
	if(b.currPos()==b.length())
		break;
	if(a.getValue()<b.getValue())
		a.next();
	else if(a.getValue()==b.getValue()){
               cout<<a.getValue()<<" ";
		b.next();
		a.next();
       }
       else if(a.getValue()>b.getValue())
		b.next();
	}
}
int main()
{
    LList<type> a,b;
    for(int i=2;i<6;i++)
    {
        a.append(i);
    }
    for(int i=0;i<5;i++)
    {
        b.append(i);
    }
    intersection(a,b);
    return 0;
}
