#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class PRE_STRING{
    private:
        int _num;
        int * _next;
        string _str;
    public:
        PRE_STRING(int n, string s);
        void count_next();  //count the next array;
        void print_pre();   //print the ans in format;
};


int main(){
    int num;  string s;
    cin>>num;
    int order = 1;
    while(num){
        cin>>s;
        PRE_STRING temp(num, s);
        temp.count_next();
        cout<<"Test case #"<<order++<<endl;
        temp.print_pre();
        cout<<endl;
        cin>>num;
    }
    return 0;
}

PRE_STRING::PRE_STRING(int n, string s){
    _num = n+1;   _str = s;
    _next = new int [_num];
}

void PRE_STRING::count_next(){
    _next[0] = -1;
    for(int i=1; i<_num; i++){
        int j = _next[i-1];
        while(_str[j]!=_str[i-1] && j>=0)
            j = _next[j];
        _next[i] = ++j;
    }
    //for(int i=0; i<_num+1; i++)   {   cout<<_next[i]<<" ";}
}

void PRE_STRING::print_pre(){
    for(int i=1; i<_num-1; i++){
        int length = i+1;
        if(length%(length-_next[length])==0&&_next[length]!=0)
            cout<<length<<" "<<length/(length-_next[length])<<endl;
    }
}