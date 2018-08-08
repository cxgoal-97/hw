#include <iostream>
#include <cstdio>

using namespace std;

class UNION_FIND{
    private:
        int _num;
        int * _parent;
        int * _relationship;
        int _count;     // 记录真话的数目
    public:
        UNION_FIND(int n);
        int find_point(int x);
        void union_point(int order, int x, int y);
        int get_count(){    return _count;}
};

int main(){
    int node_num;   int order_num;
    int x, y, order;
    cin>>node_num>>order_num;

    class UNION_FIND animal_set(node_num);

    for(int i=0; i<order_num; i++){
        cin>>order>>x>>y;
        if(x>node_num || y>node_num || x<1 || y<1 || order>3 || order<1)
            continue;
        if(x==y && order !=1 )
            continue;
        //ecout<<"第"<<i<<"句话";
        animal_set.union_point(order, x-1, y-1);
        //cout<<endl;
    }
    cout<<order_num-animal_set.get_count()<<endl;
    return 0;
}

UNION_FIND::UNION_FIND(int n){
    n++;
    _num = n;   _count = 0;
    _parent = new int [n];    _relationship = new int [n];
    for(int i=0; i<n; i++){
        _parent[i] = i;
        _relationship[i] = 0;
    }
}

int UNION_FIND::find_point(int x){
    if(_parent[x] == x)
        return x;
    int px = _parent[x];
    _parent[x] = find_point(px);
    if(_relationship[x] != _relationship[px])
        _relationship[x] = (_relationship[x] + _relationship[px] )%3;
    return _parent[x];
}

void UNION_FIND::union_point(int order, int x, int y){
    order --;
    int px = find_point(x);
    int py = find_point(y);
    if(px!=py){
        _count ++ ;
        //cout<<"祖先不同"<<"  "<<x<<"祖先为"<<px<<"  "<<y<<"祖先为"<<py;
        //cout<<"真话";
        _parent[px] = py;
        _relationship[px] = 3 - (order + _relationship[y] + 3 - _relationship[x])%3;
    }else{
        if((order+_relationship[y]+3-_relationship[x])%3==0){
            _count ++ ;
            //cout<<"真话";
        }
    }
}