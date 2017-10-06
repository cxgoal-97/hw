#include <iostream>
#include <stdlib.h>
#include "Astack.h"
using namespace std;
//判断是否为操作数
bool isOperator(string ch)
{
    string ops[]="+ - * /";
    for(int i=0;i<4;i++)
    {
        if(ch==ops[i])
            return true;
    }
    return false;
}
//比较操作数优先级
int precedence(string op1,string op2)
{
    if(op1=="(")
    {
        return -1;
    }
    if(op1=="+"||op1=="-")
    {
        if(op2=="*"||op2=="/")
            return -1;
        else
            return 0;
    }
    if(op1=="*"||op1=="/")
    {
        if(op2=="+"||op2=="-")
            return 1;
        else
            return 0;
    }
}
//转换成后缀表达式
string* convert(string inS[],Astack<string> postS1,string postS2[])
{
    int i=0;
    while(inS[i]!="\0")
    {
        if(inS[i]=="(")
            postS1.push(inS[i]);
        else if(inS[i]==")")
        {
            while(postS1.topValue()!="(")
            {
                postS2[i]=postS1.pop();
            }
            postS1.pop();
        }
        else
        {
            if(!isOperator(inS[i]))
                postS2[i]=inS[i];
            else
            {
                while(precedence(postS1.topValue(),inS[i])>=0)
                {
                    postS2[i]=postS1.pop();
                }
                postS1.push(inS[i]);
            }
        }
        i++;
    }
    while(postS1.length()!=0)
        postS2[i]=postS1.pop();
    return postS2;
}
int calculate(string postS[])
{
    Astack<int> result;
    int cal,op1,op2,finish;
    int i=0;
    while(postS[i]!="\0")
    {
        while(!isOperator(postS[i]))
        {
            result.push(atoi(&(postS[i]));
            i++;
        }
        if(postS[i]=="+")
        {
            cal=result.pop()+result.pop();
            result.push(cal);
        }
        if(postS[i]=="-")
        {
            op1=result.pop();
            op2=result.pop();
            cal=op2-op1;
            result.push(cal);
        }
        if(postS[i]=="*")
        {
            cal=result.pop()*result.pop();
            result.push(cal);
        }
        if(postS[i]=="/")
        {
            op1=result.pop();
            op2=result.pop();
            cal=op2/op1;
            result.push(cal);
        }
        i++;
    }
    finish=result.pop();
    return finish;
}
int main()
{
    Astack<string> postS1;
    string postS2[20];
    string inS[20];
    int result;
    cout<<"please input formula, finish by '#':\n";
    string input;
    int i=0;
    //读入计算式
    while(input!="#")
    {
        cin>>input;
        inS[i]=input;
        i++;
    }
    i=0;
    postS2=convert(inS,postS1,postS2);
    cout<<"中缀表达式：\n";
    while(inS[i]!="\0")
    {
        cout<<inS[i];
        i++;
    }
    cout<<"\n后缀表达式：\n";
    postS2.print();
    result=calculate(postS2);
    cout<<"the result is:"<<result<<endl;
    return 0;
}
