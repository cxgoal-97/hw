#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
struct node{
    char val;
    struct node * left;
    struct node * right;
};

class textTree{
    private:
        int num;
        struct node* root;
        vector<struct node*> now_father;
        int getCnt(string s){
            int i=0;
            while(s[i++]=='-');
            return i-1;
        }
        char getChar(string s){ return s[s.size()-1];}
        void print_pre_help(struct node * root);
        void print_ino_help(struct node * root);
        void print_last_help(struct node * root);
    public:
        textTree(){ num=0; root=NULL; now_father.push_back(root); }
        void insert(string s);
        void print_pre() { print_pre_help(now_father[0]);};
        void print_ino() { print_ino_help(now_father[0]);};
        void print_last() { print_last_help(now_father[0]);};
        void print(){   cout<<now_father[0]->val<<endl;
        }// cout<<now_father[0]->left->val;}
};

int main(){
    int N;  // num of tree;
    cin>>N;
    cin.get();
    string s;
    for(int i=0; i<N; i++){
        class textTree T;
        getline(cin, s);
        while(s!="0"){
            T.insert(s);
            getline(cin, s);
        }

        T.print_pre();
        cout<<endl;
        T.print_last();
        cout<<endl;
        T.print_ino();
        cout<<endl;
        if(i!=N)
            cout<<endl;
    }
    return 0;
}

void textTree::print_last_help(struct node* root){
    if(root==NULL || root->val == '*')
        return;
    print_last_help(root->left);
    print_last_help(root->right);
    cout<<root->val;
}

void textTree::print_ino_help(struct node* root){
    if(root==NULL || root->val == '*')
        return;
    print_ino_help(root->left);
    cout<<root->val;
    print_ino_help(root->right);
}

void textTree::print_pre_help(struct node* root){
    if(root==NULL || root->val == '*')
        return ;
    cout<<root->val;
    print_pre_help(root->left);
    print_pre_help(root->right);
}

 void textTree::insert(string s){
     num++;
     int level = getCnt(s);
     char val = getChar(s);
     struct node* n_node = new struct node;
     n_node->val = val;
     //cout<<"val"<<val<< "level"<<level<<endl;
     n_node->left = NULL;
     n_node->right = NULL;
     if(level > (int)now_father.size()-1 ){
         now_father.push_back(n_node);
     }
     else
         now_father[level] = n_node;
     if(level==0)
         return;
     if(now_father[level-1]->left != NULL)
         now_father[level-1]->right = n_node;
     else
         now_father[level-1]->left = n_node;
 }
