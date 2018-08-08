#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

struct node{
    char c;
    struct node* left;
    struct node* right;
    int height;
};

class infix{
    private:
        struct node* _root;
        int _variable_num;
        int _hashTable[256];
        char **  _printTable;
        int _level;
        void _plot_create_help(struct node * root, int x, int y, int tag);
        int _compute_help(struct node * root);
        void _post_print_help(struct node * root);
    public:
        infix(string infix, int n);
        string insert_left_brackets(string s, int index);
        string insert_right_brackest(string s, int index);
        struct node * get_root(string infix, int left, int right, int height);
        void post_print();
        void plot_create();
        void plot_print();
        int compute();
};

int main(){
    string s;   int n;
    cin>>s>>n;
    class infix INFIX(s, n);
    INFIX.post_print(); cout<<endl;
    //INFIX.plot_create();
    //INFIX.plot_print();
    cout<<INFIX.compute();
    return 0;
}
void infix::plot_create(){
    _printTable = new char *[2*_level-1];
    for(int i=0; i<2*_level-1; i++){
        _printTable[i] = new char [1+2*(_level-1)];
        for(int j=0; j<1+4*(_level-1); j++)
            _printTable[i][j] = ' ';
    }
    _plot_create_help(_root, 0, _level-1, 0);
}
void infix::_plot_create_help(struct node *root, int x, int y, int tag){
    if(root==NULL)
        return ;
    if(!(root->c>='a'&&root->c<='z')){
        _printTable[x][y] = root->c;
        _printTable[x+1][y-1] = '/';
        _plot_create_help(root->left, x+2, y-1, -1);
        _printTable[x+1][y+1] = '\\';
        _plot_create_help(root->right, x+2, y+1, 1);
    }else if(x==2*_level-2){
        _printTable[x][y] = root->c;
    }else{
        _printTable[x][y+tag] = root->c;
    }
}
void infix::plot_print(){
    for(int i=0; i<2*_level-1; i++){
        for(int j=0; j<1+4*(_level-1); j++){
            cout<<_printTable[i][j];
        }
        cout<<endl;
    }
}
infix::infix(string infix, int n){
    // 插入 * & /
    int i = 0;
    while(infix[i]!='\0'){
        if(infix[i]=='*'||infix[i]=='/'){
            if(infix[i-2]=='('&&infix[i+2]==')')    {i++;   continue;}
            infix = insert_left_brackets(infix, i);
            i = i+1;
            infix = insert_right_brackest(infix, i);
        }
        i++;
    }
    // 插入 + & -
    i = 0;
    while(infix[i]!='\0'){
        if(infix[i]=='+'||infix[i]=='-'){
            if(infix[i-2]=='('&&infix[i+2]==')')    {i++;   continue;}
            infix = insert_left_brackets(infix, i);
            i = i+1;
            infix = insert_right_brackest(infix, i);
        }
        i++;
    }
    //
    _root = get_root(infix, 0, infix.size()-1, 1);
    // n is the num of variable;
    char t_char; int t_num;
    for(int i=0; i<n; i++){
        cin>>t_char>>t_num;
        _hashTable[(int)t_char] = t_num;
    }
    _variable_num = n;
    cout<<endl<<infix<<endl;
}
void infix::post_print(){
    _post_print_help(_root);
}
void infix::_post_print_help(struct node * root){
    if(root==NULL)
        return;
    _post_print_help(root->left);
    _post_print_help(root->right);
    cout<<root->c;
}
struct node* infix::get_root(string infix, int left, int right, int height){
    if(left > right)
        return NULL;
    int t = left;
    int count_left_brackets = 0;
    while(t<right){
        if(infix[t]=='(')
            count_left_brackets++;
        else if(infix[t]==')')
            count_left_brackets--;
        else if(count_left_brackets==1 && !(infix[t]>='a'&&infix[t]<='z')){
            break;
        }
        t++;
    }
    struct node* p = new struct node;
    p->c = infix[t];
    p->height = height;
    _level = max(_level, height);
    p->left = get_root(infix, left+1, t-1, height+1);
    p->right = get_root(infix, t+1, right-1, height+1);
    return p;
}
string infix::insert_left_brackets(string s, int index){
    //在index前插入括号
    // insert the right brackets
    int t = index - 1;
    int count_right_brackets = 0;
    while(t>0){
        if(s[t]==')')
            count_right_brackets ++;
        else if(s[t]=='(')
            count_right_brackets --;
        if(count_right_brackets==0)
            break;
        t--;
    }
    s.insert(s.begin()+t, '(');
    return s;
}
string infix::insert_right_brackest(string s, int index){
    int t = index + 1;
    int count_left_brackets = 0;
    while(t < (int)s.size()){
        if(s[t]=='(')
            count_left_brackets++;
        else if(s[t]==')')
            count_left_brackets--;
        else if(count_left_brackets==0){
            s.insert(s.begin()+t+1, ')');
            return s;
        }
        t++;
    }
    s.push_back(')');
    return s;
}
int  infix::compute(){
    return _compute_help(_root);
}
int infix::_compute_help(struct node * root){
    if(root->c=='+')
        return _compute_help(root->left)+_compute_help(root->right);
    else if(root->c=='-')
        return _compute_help(root->left)-_compute_help(root->right);
    else if(root->c=='*')
        return _compute_help(root->left)*_compute_help(root->right);
    else if(root->c=='/')
        return _compute_help(root->left)/_compute_help(root->right);
    return _hashTable[root->c];
}