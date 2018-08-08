#include <cstdio>
#include <iostream>

using namespace std;

class heap{
    private:
        int _num;
        int _array[100000];
    public:
        heap(){ _num = 0;}
        void insert(int val);
        void pop();
        int top(){  return _array[1];};
};

int main(){
    int N;
    cin>>N;
    for(int i=0; i<N; i++){
        int K, order, num;
        cin>>K;
        class heap H;
        for(int j=0; j<K; j++){
            scanf("%d", &order);
            switch (order){
                case 1:
                    scanf("%d", &num);
                    H.insert(num);
                    break;
                case 2:
                    printf("%d\n", H.top());
                    H.pop();
            }
        }
    }
    return 0;
}

void heap::insert(int val){
    int index = ++_num;
    while(index>1 && _array[index/2] > val){
        _array[index] = _array[index/2];
        index /= 2;
    }
    _array[index] = val;
}

void heap::pop(){
    _array[1] = _array[_num--];
    int index = 1;
    int next = index*2;
    while(next <= _num){
        if(next+1 <= _num && _array[next] > _array[next+1])
            next++;
        if(_array[next] > _array[index])
            break;
        swap(_array[index],_array[next]);
        index = next;
        next = index *2;
    }
}
