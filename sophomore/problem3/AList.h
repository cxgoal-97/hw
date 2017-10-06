#ifndef ALIST_H_INCLUDED
#define ALIST_H_INCLUDED
#include <iostream>
#include <assert.h>
using namespace std;
template <typename E>//array based list implementation
class AList
{
private:
	int maxSize;//maximum size of list
	int listSize;//number of list items now
	int curr;//position of current element
	E* listArray;//array holding list elements
public:
	AList(int size=10)//constructor
    {
	maxSize=size;
	listSize=curr=0;
	listArray=new E[maxSize];
	}
	~AList(){delete [] listArray;}//destructor
	void clear(){
		delete [] listArray;
		listSize=curr=0;
		listArray=new E[maxSize];
	}
	//insert element 'it' at current position
	void insert(const E& it){
		assert(listSize<maxSize);
		for(int i=listSize;i>curr;i--)
			listArray[i]=listArray[i-1];
		listArray[curr]=it;
		listSize++;
	}
	void append(const E& it)
	{
		assert(listSize<maxSize);
		listArray[listSize++]=it;
	}
	//remove and return the current element
	E remove()
	{
		assert((curr>=0)&&(curr<=listSize));
		E it=listArray[curr];
		for(int i=curr;i<listSize-1;i++)
			listArray[i]=listArray[i+1];
		listSize--;
		return it;
	}
	void moveToStart(){curr=0;}
	void moveToEnd(){curr=listSize;}
	void prev(){
		if(curr!=0)
			curr--;
	}
	void next(){
		if(curr<listSize)
			curr++;
	}
	int length() const{return listSize;}
	int currpos() const{return curr;}
	void moveToPos(int pos){
		assert((pos>=0)&&(pos<=listSize));
		curr=pos;
	}
	const E& getValue() const{
		assert((curr>=0)&&(curr<listSize));
		return listArray[curr];
	}
};
#endif // ALIST_H_INCLUDED
