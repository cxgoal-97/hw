#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int main(){
    queue <int> que;
    for(int i = 0; i<5; i++){
        que.push(2*i+4);
    }
    cout<<que.front()<<endl;
    que.pop();
    cout<<que.front();
}
