#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;


struct node{
    int val;
    struct node * l_p;
    struct node * r_p;
};

struct node * get_root_p(int ino_l, int ino_r, int post_l, int post_r);
void pre_order(struct node * root);

vector<int> num_in_array;
vector<int> num_post_array;
vector<struct node> node_list;

int cnt = 0;

int main(){
    int c;
    while(1){
        cin>>c;
        num_in_array.push_back(c);
        if(cin.get()!=' ')
            break;
    }
    while(1){
        cin>>c;
        num_post_array.push_back(c);
        if(cin.get()!=' ')
            break;
    }
/*  */
    struct node *root = get_root_p(0, num_post_array.size()-1, 0, num_post_array.size()-1);
    pre_order(root);

    return 0;
}


struct node * get_root_p(int ino_l, int ino_r, int post_l, int post_r){
    if(ino_l>ino_r || post_l>post_r)
        return NULL;
    int root_val = num_post_array[post_r];   //获取当前根的数字
    int index = ino_r;
    while(index>=ino_l&&num_in_array[index]!=root_val)  {index--;}

    int l_size = index - ino_l;

    struct node* t = new struct node;
    t->val = root_val;
    t->l_p = get_root_p(ino_l, ino_l+l_size-1, post_l, post_l+l_size-1);
    t->r_p = get_root_p(index+1, ino_r, post_l+l_size, post_r-1);

    return t;
}

void pre_order(struct node * root){
    if(root==NULL)
        return ;
    else{
        cout<<root->val;
        cnt++;
        if(cnt!=num_in_array.size())
            cout<<" ";
        pre_order(root->l_p);
        pre_order(root->r_p);
    }
}
