#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

struct node{
    char data;
    vector<struct node *> child;
};
class TREE{
    private:
        vector<struct node *> _root;       
        void _post_print_help(struct node * _root);
        int _num;
    public:
        TREE(int n);
        void post_print(){
            for(int i=0; i<_root.size(); i++)
                _post_print_help(_root[i]);
        };
};

int main(){
    int n;  cin>>n;
    class TREE tree(n);
    tree.post_print();
    cout<<endl;
    return 0;
}

TREE::TREE(int n){
    vector<struct node *> node_list;
    vector<int > child_num;
    char t_c; int num;
    _num = 0;
    for(int i=0; i<n; i++){
        char temp = 'c';
        while(temp!='\n'){
            cin>>t_c>>num;
            struct node* t = new struct node;  
            t->data = t_c; 
            node_list.push_back(t);
            child_num.push_back(num);
            temp = getchar();
            _num++;
        }
        _root.push_back(*node_list.begin());
        int k = 1;
        for(int j=0; j < node_list.size(); j++){
            if(child_num[j]!=0){
                int m;
                for(m=0; m<child_num[j]; m++){
                    node_list[j]->child.push_back(node_list[m+k]);                             
                }
                k = k+m;
            }
        }
        node_list.clear();  child_num.clear();
    }
    
}

void TREE::_post_print_help(struct node*  root){
    if(root==NULL)
        return ;
    for(int i=0; i< root->child.size(); i++){
        _post_print_help(root->child[i]);
    }
    cout<<root->data;
    _num--;
    if(_num!=0)
        cout<<" ";
}