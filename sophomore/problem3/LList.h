#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED
#include <iostream>
#include <assert.h>
#include "node.h"
using namespace std;
template<typename E>class LList
{
private:
	Link<E> *head;
	Link<E> *tail;
	Link<E> *curr;
	int cnt;//size of list
	void init(){//initialization helper method
		curr=head=tail=new Link<E>;
		cnt=0;
	}
	void removeall(){//return link node to free store
		while(head!=NULL){
			curr=head;
			head=head->next;
			delete curr;
		}
	}
public:
	LList(int size=10){init();}//constructor
	~LList(){removeall();}//destructor
	void print() const;//print list contents
	void clear(){removeall();init();}//clear list
	void insert(const E& it){//insert "it" at current position
		curr->next=new Link<E>(it,curr->next);
		if(tail==curr)
			tail=curr->next;
		cnt++;
	}
	void append(const E& it){
		tail=tail->next=new Link<E>(it,NULL);
		cnt++;
	}
	E remove()//remove and return current element
	{
		Assert(curr->next!=NULL,"no element");
		E it=curr->next->element;
		Link<E> *itemp=curr->next;
		if (tail==curr->next) tail=curr;
		curr->next=curr->next->next;
		delete itemp;
		cnt--;
		return it;
	}
	void moveToStart(){curr=head;}
	void moveToEnd(){curr=tail;}
	void prev(){
		if(curr==head)
			return;
		Link<E> *temp=head;
		while(temp->next!=curr)
            temp=temp->next;
			curr=temp;
	}
	void next(){
		if(curr!=tail)
			curr=curr->next;
	}
	int length() const{
		return cnt;
	}
	int currPos() const{
		Link<E>* temp=head;
		int i;
		for(i=0;curr!=temp;i++)
			temp=temp->next;
		return i;
		}
	void moveToPos(int pos){
		assert((pos>=0)&&(pos<=cnt));
		curr=head;
		for(int i=0;i<pos;i++)curr=curr->next;
	}
	const E& getValue() const{
		assert(curr->next!=NULL);
		return curr->next->element;
	}
};
#endif // LLIST_H_INCLUDED
