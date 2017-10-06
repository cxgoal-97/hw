#include <iostream>
#include <assert.h>
#include "Stack.h"
#include "AStack.h"
#include "element.h"
#include <stdlib.h>	// For using the strtod


int isOperator(char c);
//get the priority of the operator
int getOperPri(char c);
//if left is more important than right, return 1
//if the priority of a is the same as b, reutrn 0
//else return -1;	
int comPare(char left, char right);

using std::cin;
using std::cout;
using std::endl;

int main(){
	//Step 1
	char str[1000];
	cin>>str;
	AStack<char> oStack;
	AStack<element> result;

	char* po=str;
	double nu;

	while(*po!='\0'){
		if(isOperator(*po)){
			char c = *po;
			po++;
			//Now we have get the element, we need to use it
			//First if the Stack is empty, we push it without any hesitation.
			if(oStack.length()==0){
				oStack.push(c);
			}
			//Now the Stack is not empty, so we need to compare the priority of
			//the our element  and the top of the Stack
			//if our element is over than or the same as top
			else{
				char top = oStack.topValue();
				if(c==')'){
					while(top!='('){
						char t = oStack.pop();
						element temp;
						temp.setOper(t);
						result.push(temp);
						top = oStack.topValue();
					}
					oStack.pop();
				}
				else if(c=='('){	oStack.push(c);}
				else if(comPare(top,c)>-1){
					while(comPare(top,c)!=-1){
						char t = oStack.pop();
						element temp;
						temp.setOper(t);
						result.push(temp);
						if(oStack.length()==0)
							break;
						top = oStack.topValue();
					}
					oStack.push(c);
				}
				else{	oStack.push(c);}
			}
		}
		else{
			element temp;
			nu = strtod(po,&po);
			temp.setNumber(nu);
			result.push(temp);
		}
	}
	while(oStack.length()!=0){
		char t = oStack.pop();
		element temp;
		temp.setOper(t);
		result.push(temp);
	}
	int len = result.length();
	
	
	AStack<element> show;
	for(int i=0;i<len;i++)
		show.push(result.pop());
	
	
	AStack<double> numStack;

 	for(int i=0;i<len;i++){
		element t = show.pop();
		result.push(t);
		if(t.status()==0){
			cout<<t.getNum()<<"   ";
			numStack.push(t.getNum());
			
		}
		else{
			cout<<t.getOper()<<"   ";
			double a=numStack.pop();
			double b=numStack.pop();
			char op = t.getOper();
			if(op=='+')
				numStack.push(a+b);
			else if(op=='-')
				numStack.push(b-a);
			else if(op=='*')
				numStack.push(a*b);
			else if(op=='/')
				numStack.push(b/a);
		}
	}
	cout<<endl<<"The result is "<<numStack.topValue()<<endl;
	return 0;
}

int isOperator(char c){
	if(c>='0'&&c<='9')
		return 0;
	return 1;
}

//get the priority of the operator
int getOperPri(char c){
	if(c=='+'||c=='-')
		return 0;
	if(c=='*'||c=='\\')
		return 1;
	if(c=='('||c==')')
		return -1;
}

int comPare(char left, char right)	
{
	if(getOperPri(left)>getOperPri(right))
		return 1;
	else if(getOperPri(left)==getOperPri(right))
		return 0;
	else
		return -1;
}
