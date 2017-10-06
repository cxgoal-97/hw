#ifndef ASTACK_H_INCLUDED
#define ASTACK_H_INCLUDED
//#include "Stack.h"
#include "assert.h"
using namespace std;
template <typename E> class Astack
{
private:
    int maxSize;
    int top;
    E *listArray;

public:
    //constructor
    Astack(int size=20)
    {
        maxSize=size;
        top=0;
        listArray=new E[size];
    }
    //destructor
    ~Astack(){delete [] listArray;}
    //reinitialize
    void clear() {top=0;}
    //push 'it' on stack
    void push(const E& it)
    {
        assert(top!=maxSize);//error
        listArray[top++]=it;
    }
    //pop top element
    E pop()
    {
        assert(top!=0);//error
        return listArray[--top];
    }
    const E& topValue() const
    {
        assert(top!=0);
        return listArray[top-1];
    }
    //return length
    int length() const {return top;}
    void print()
    {
        for(int i=0;i<maxSize;i++)
            cout<<listArray[i];
    }
};


#endif // ASTACK_H_INCLUDED
