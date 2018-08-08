#include<iostream>
#include<stack>
#include<vector>

using namespace std;

int sum;
void diGui(stack<int> S, vector<int> array);
int main(){
    sum = 0;
    int n;
    cin>>n;
    stack<int> S;
    vector<int> array;
    for(int i=0; i<n; i++)
        array.push_back(i);
    diGui(S, array);
    cout<<sum;
    return 1;
}

void diGui(stack<int> S, vector<int> array){
    if(array.size()==0){
        sum++;
        return ;
    }
    S.push(1);
    array.erase(array.begin()+0);
    diGui(S,array);
    S.pop();
    array.push_back(1);
    if(S.size()!=0){
        //如果可以出就出
        S.pop();
        diGui(S,array);
    }
}
