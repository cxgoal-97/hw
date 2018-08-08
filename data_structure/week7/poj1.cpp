#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

// Huffman coding


priority_queue<int, vector<int>, greater<int> > Q;

int main(){
    int N;
    int t;
    cin>>N;
    for(int i=0; i<N; i++){
        scanf("%d", &t);
        Q.push(t);
    }

    int sum = 0;
    int a,b;
    while(Q.size()!=1){
        a = Q.top();    Q.pop();
        b = Q.top();    Q.pop();
        sum += (a+b);
        Q.push(a+b);
    }

    cout<<sum;
    return 0;
}
