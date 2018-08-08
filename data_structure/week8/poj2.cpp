#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct binary_tree_node{
    char data;
    struct binary_tree_node * left;
    struct binary_tree_node * right;
    binary_tree_node(char d){ data = d; left = NULL; right = NULL;}
};

struct tree_node{
    char data;
    vector<struct tree_node *> child;
    tree_node(char d) {data = d;}
};

class TREE{
    private:
        int _num;
        struct binary_tree_node * _binary_root;
        struct tree_node * _root;
        void getSymmetricTree_help(struct tree_node * root);
        void binary_tree_post_print_help(struct  binary_tree_node * binary_root);
    public:
        TREE(int n);
        void binaryTree2Tree();
        void getSymmetricTree() {getSymmetricTree_help(_root);};
        void tree_level_print();
        void binary_tree_post_print() { binary_tree_post_print_help(_binary_root);};
};
void TREE::getSymmetricTree_help(struct tree_node * root){
    if(root == NULL)
        return ;
    reverse(root->child.begin(), root->child.end());
    for(int i=0; i<root->child.size(); i++){
        getSymmetricTree_help(root->child[i]);
    }
}
void TREE::binary_tree_post_print_help(struct binary_tree_node * binary_root){
    if(binary_root == NULL)
        return ;
    binary_tree_post_print_help(binary_root->left);
    binary_tree_post_print_help(binary_root->right);
    cout<<binary_root->data<<" ";
}
void TREE::tree_level_print(){
    int j = 0;
    struct tree_node *t = _root;
    //cout<<t->data<<" "<<t->child[1]->data<<" "<<t->child[1]->child[0]->data<<" "<<endl;
    queue<struct tree_node * > S;
    S.push(t);
    while(!S.empty()){
        t = S.front();
        cout<<t->data;
        if((++j)!=_num)
            cout<<" ";
        S.pop();
        for(int i=0; i<t->child.size(); i++){
            S.push(t->child[i]);
        }
    }
}
void TREE::binaryTree2Tree(){
    _root = new struct tree_node(_binary_root->data);
    stack<struct binary_tree_node *> S;
    stack<struct tree_node *> tree_S;
    S.push(_binary_root);
    while(!S.empty()){
        struct binary_tree_node * temp_root = S.top();
        S.pop();
        struct tree_node * temp_root_before = _root;
        //找到 S.data 代表的 节点
        while(!tree_S.empty()){tree_S.pop();}
        tree_S.push(_root);
        while(!tree_S.empty()){
            struct tree_node * t = tree_S.top();
            if(t->data==temp_root->data){  temp_root_before = t; break;}
            tree_S.pop();
            for(int i=0; i<t->child.size(); i++){
                tree_S.push(t->child[i]);
            }
        }
        //cout<<"此时母节点为"<<temp_root_before->data<<endl;
        if(temp_root->left != NULL){
            temp_root = temp_root->left;
            while(temp_root!=NULL){
                //cout<<"  右边为"<<temp_root->data;
                struct tree_node * t = new struct tree_node(temp_root->data);
                temp_root_before ->child.push_back(t);
                //cout<<temp_root_before->data<<"插入"<<t->data<<endl;
                S.push(temp_root);
                temp_root = temp_root->right; 
            }    
        }
    }
}
TREE::TREE(int n){
    // 将输入转化为一个二叉树
    stack<struct binary_tree_node *> S;
    _num = n;
    char data; int tag;
    for(int i=0; i<n; i++){
        cin>>data>>tag;
        struct binary_tree_node * temp_node = new struct binary_tree_node(data);        
        if(i==0)    {_binary_root = temp_node;};
        if(!S.empty()){
            if(S.top()->left==NULL){
                S.top()->left = temp_node;
            }else if(S.top()->right==NULL){
                S.top()->right = temp_node;
                S.pop();
            }
        }
        if(tag==0){ S.push(temp_node) ; }
    }
    // 将$设置为空
    while(!S.empty())   {S.pop();}
    S.push(_binary_root);
    while(!S.empty()){
        struct binary_tree_node * temp_node = S.top();
        S.pop();
        if(temp_node->left!=NULL){
            if(temp_node->left->data == '$'){
                temp_node->left = NULL;
                _num--;
            }
            else{
                S.push(temp_node->left);   
            }
        }
        if(temp_node->right!=NULL){
            if(temp_node->right->data == '$'){
                temp_node->right = NULL;
                _num--;
            }
            else{
                S.push(temp_node->right);
            }
        }
    }
    
}

int main(){
    int n;  cin>>n;
    class TREE tree(n);
    //tree.binary_tree_post_print();
    tree.binaryTree2Tree();
    tree.getSymmetricTree();
    tree.tree_level_print();
    cout<<endl;
    return 0;
}