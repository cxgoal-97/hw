#include <iostream>
#include "BSTNode.h"
using std::cout;
using std::string;

template <typename Key,typename E>class BST {
	private:
		BSTNode<Key,E>* root;
		int nodecount;

		void clearhelp(BSTNode<Key,E>*);

		BSTNode<Key,E>* inserthelp(BSTNode<Key,E>*,const Key&,const E&);
		BSTNode<Key,E>* deletemin(BSTNode<Key,E>*);
		BSTNode<Key,E>* getmin(BSTNode<Key,E>*);
		BSTNode<Key,E>* removehelp(BSTNode<Key,E>*,const Key&);
		E* findhelp(BSTNode<Key,E>*,const Key&) const ;
		void printhelp(BSTNode<Key,E>*,int ) const ;

		//In the probble we need
		void printByCharHelp(BSTNode<Key,E>*,int ,char) const ;
		void printByDisHelp(BSTNode<Key,E>*,int ,double,double, double ) const ;
	public:
		BST()	{root = NULL;nodecount = 0;}
		~BST()	{clearhelp(root);}

		void clear(){
			clearhelp(root); root = NULL ; nodecount = 0;}

		void insert(const Key & k,const E& e){
			root = inserthelp(root,k,e);
			nodecount++;
		}

		E remove(const Key& k){
			E* temp = findhelp(root,k);
			if(temp != NULL){
				root = removehelp(root,k);
				nodecount--;
				return *temp;
			}else{
				cout<<"The Node is not exit\n";
			}
		}

		E removeAny(){
			if(root!=NULL){
				E temp = root->element();
				root = removehelp(root,root->Key());
				nodecount--;
				return temp;
			}
			else return NULL;
		}

		E* find(const Key& k)const {	return findhelp(root,k);}
		int size()	{return nodecount;}
		void print() const {
			if(root == NULL)	cout<<"The BST is empty.\n";
			else printhelp(root,0);
		}

		//We need to 
		void printByChar(char c){
			if(root == NULL)	cout<<"The BST is empty.\n";
			else printByCharHelp(root,0,c);
		}
		void printByDis(double x,double y, double dis){
			if(root ==NULL)	cout<<"The BST is empty.\n";
			else
				printByDisHelp(root,0,x,y,dis);
		}
};

template <typename Key,typename E>
E* BST<Key,E>::
findhelp(BSTNode<Key, E>*root,const Key &k) const{
	if (root ==NULL)	return NULL;
	if (k < root->key())
		return findhelp(root->left(),k);
	else if (k > root->key())
		return findhelp(root->right(),k);
	else	return &(root->element());
}

template <typename Key,typename E>
BSTNode<Key,E> *BST<Key,E>::
inserthelp(BSTNode<Key,E>* root,const Key& k, const E& it){
	if( root == NULL)
		return new BSTNode<Key,E>(k,it,NULL,NULL);
	if( k < root->key())
		root->setLeft(inserthelp(root->left(),k,it));
	else
		root->setRight(inserthelp(root->right(),k,it));
	return root;
}

template <typename Key,typename E>
BSTNode<Key,E>* BST<Key,E>::
deletemin(BSTNode<Key,E>* rt){
	if(rt->left() == NULL)
		return rt->right();
	else{
		rt->setLeft(deletemin(rt->left()));
		return rt;
	}
}
template <typename Key,typename E>
BSTNode<Key,E>* BST<Key,E>::
getmin(BSTNode<Key,E>*rt){
	if(rt -> left() == NULL)
		return rt;
	else	return getmin(rt->left());
}

template <typename Key,typename E>
BSTNode<Key, E>* BST<Key,E>::
removehelp(BSTNode<Key, E>*rt,const Key& k){
	if (rt==NULL)	return NULL;
	else if(k<rt->key())
		rt->setLeft(removehelp(rt->left(),k));
	else if(k>rt->key())
		rt->setRight(removehelp(rt->right(),k));
	else{
		BSTNode<Key,E>* temp = rt;
		if(rt->left()==NULL){
			rt = rt->right();
			delete temp;
		}
		else if(rt->right()==NULL){
			rt = rt->left();
			delete temp;
		}
		else{
			BSTNode<Key,E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

template<typename Key,typename E>
void BST<Key,E>::clearhelp(BSTNode<Key,E>* root) {
	if (root==NULL)	return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

template<typename Key,typename E>
void BST<Key,E>::
printhelp(BSTNode<Key,E>* root,int level) const {
	if (root ==NULL)	return ;
	printhelp(root->left(),level+1);
	for(int i=0;i<level;i++)
		cout<<" ";
//	cout<<root->key()<<"\n";
//	
	E it = root->element();
	cout<<it.getName()<<" x:"<<it.getPosX()<<" y:"<<it.getPosY()<<"\n";
	printhelp(root->right(),level+1);
}

template<typename Key,typename E>
void BST<Key,E>::
printByCharHelp(BSTNode<Key,E>* root,int level,char c) const{
	if (root ==NULL) 	return ;
	printByCharHelp(root->left(),level+1,c);
	printByCharHelp(root->right(),level+1,c);
	E it = root->element();
	if(it.getName()[0]==c)
		cout<<it.getName()<<" x:"<<it.getPosX()<<" y:"<<it.getPosY()<<"\n";
}

template<typename Key,typename E>
void BST<Key,E>::
printByDisHelp(BSTNode<Key,E>* root,int level,double x,double y,double dis) const{
	if (root == NULL)	return ;
	printByDisHelp(root->left(),level+1,x,y,dis);
	printByDisHelp(root->right(),level+1,x,y,dis);
	E it = root -> element();
	double disX = x-it.getPosX();
	double disY = y-it.getPosY();
	if(disX*disX+disY*disY<=dis*dis)
		cout<<it.getName()<<" x:"<<it.getPosX()<<" y:"<<it.getPosY()<<"\n";
}
