#include <iostream>
#include <cstdio>

using namespace std;

struct node{
    int value;
    struct node* l;
    struct node* r;
};

int sum = 0;
struct node * insert(int value, struct node * root);
void pre_order(struct node* root);

int main(){
    struct node* root = NULL;
    int num = 0;

    while(scanf("%d",&num)){
        root = insert(num, root);
        if(getchar()!=' ')
            break;
    }

    pre_order(root);
    cout<<endl;
    return 0;
}

struct node * insert(int value, struct node * root){
    if(root==NULL){
        root = new struct node;
        root->value = value;
        root->l = NULL;
        root->r = NULL;
        sum++;
    }else if(value> root->value){
        root->r = insert(value, root->r);
    }else if(value< root->value){
        root->l = insert(value, root->l);
    }
    return root;
}

void pre_order(struct node* root){
    if(root==NULL)
        return ;
    else{
        cout<<root->value;
        if(--sum!=0)
            cout<<" ";
        pre_order(root->l);
        pre_order(root->r);
    }
}
