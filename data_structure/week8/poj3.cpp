#include <iostream>
#include <cstdio>

using namespace std;

class UNION_FIND{
    private:
        int _num;
        int * _father_list;     // -1 代表自己是自己的祖先
        int * _relation_list;   // 0 代表和祖先是同类， 1代表吃祖先， 2代表被祖先吃
        int _count;
    public:
        UNION_FIND(int n){
            _num = n; _count = 0;
            _father_list =  new int [n];    _relation_list = new int [n];
            for(int i=0; i<n; i++){ _father_list[i] = -1; _relation_list[i] = 0;}
           }
        int get_father(int n){
            if(_father_list[n]==-1)
                return n;
            else{
                int t = _father_list[n];
                _father_list[n] = get_father(t);
                int tag = 0;
                 
                if(_relation_list[n]==2 && _relation_list[t]==2)    {tag = 1;}
                if(_relation_list[n]==1 && _relation_list[t]==1)    {tag = -1;}
                _relation_list[n] = (tag + _relation_list[n] + _relation_list[t]) % 3;
                return _father_list[n];
            }
        }
        void join(int d, int m, int n){
            d--;
            //d: 0代表m和n同类， 1代表m吃n
            int fm = get_father(m);
            int fn = get_father(n);
            if(fm!=fn){
                _father_list[fn] = fm;
                _relation_list[fn] = 3-(d + 3-_relation_list[m] +_relation_list[n])%3;
                _count ++ ;
            }else{
                // 有关系
                // 检查是否相容
                if( 0== (d + _relation_list[n]+3-_relation_list[m])%3){// 相容，
                    _count ++ ;
                }
            }
        }
        int get_count(){
            return _count;
        }
};

int main(){
    int order_list, num;
    cin>>num>>order_list;
    class UNION_FIND food_chain(num);
    int order, active, passive;
    for(int i=0; i<order_list; i++){
        cin>>order>>active>>passive;
        if(active<=num && passive<=num  && !(order!=0 && passive==active)){
            food_chain.join(order, active-1, passive-1);
        }
    }
    cout<<order_list-food_chain.get_count()<<endl;
}
