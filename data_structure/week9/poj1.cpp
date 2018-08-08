#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
#define INF 999999999

class G{
    private:
        int _num;
        int ** _matrix;
        map<string, int> _string2int;
        string * _int2string;
        int * _parent;
    public:
        G(int n);
        void dij(string s_begin, string s_end);
};

int main(){
    /* code */
    int n;  cin>>n;
    class G graph(n);
    string s_begin, s_end;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>s_begin>>s_end;
        cout<<endl;
        graph.dij(s_begin, s_end);
    }
    return 0;
}
void G::dij(string s_begin, string s_end){
    vector<int > ans;
    int begin = _string2int[s_begin];   int end = _string2int[s_end];
    // clear the _parent
    for(int i=0; i<_num; i++){ _parent[i]=-1;}
    // init the distance
    int * distance = new int [_num];
    bool * visited = new bool [_num];
    for(int i=0; i<_num; i++){ distance[i]=_matrix[begin][i];   visited[i] = false;}
    // 开始n次循环
    while(1){
        //pick the minimum
        int index = -1;
        int min_distance = INF;
        for(int i=0; i<_num; i++){
            if(visited[i]==false && distance[i]<min_distance){
                index = i;  min_distance = distance[i];
            }
        }
        if(index==-1)   {break;}
        // 修改并更新
        visited[index] = true;
        for(int i=0; i<_num; i++){
            if(visited[i]==false && distance[index]+_matrix[index][i] < distance[i]){
                distance[i] = distance[index]+_matrix[index][i];
                _parent[i] = index;
            }
        }
    }
    int t = end;
    while(t!=-1){
        ans.push_back(t); 
        t = _parent[t];
    }
    reverse(ans.begin(), ans.end());
    cout<<s_begin;
    if(ans.size()!=1)   {ans.insert(ans.begin(), begin);}
    for(int i=1; i<ans.size(); i++){
        cout<<"->("<<_matrix[ans[i-1]][ans[i]]<<")->"<<_int2string[ans[i]];
    }
}
G::G(int n){
    _num = n;
    _matrix = new int* [n];
    _int2string = new string [n];
    _parent = new int [n];
    //邻接矩阵的初始化
    //输入n 个地点
    string temp;
    for(int i=0; i<n; i++){
        cin>>temp;
        _string2int.insert(map<string, int>::value_type(temp, i));
        _int2string[i] = temp;
        _matrix[i] = new int [n];
        for(int j=0; j<n; j++){
            _matrix[i][j] = INF*(i!=j);
        }
    }
    //n 代表路的个数
    cin>>n;
    string temp1; int distance;
    for(int i=0; i<n; i++){
        cin>>temp>>temp1>>distance;
        int temp_start = _string2int[temp];
        int temp_end = _string2int[temp1];
        _matrix[temp_start][temp_end] = min(distance, _matrix[temp_start][temp_end]);
        _matrix[temp_end][temp_start] = _matrix[temp_start][temp_end];
    }

}