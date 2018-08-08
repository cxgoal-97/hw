#include <iostream>
#include <cstdio>

#define INF 100000
using namespace std;

class G{
    private:
        int _node_num;
        int _edge_num;
        int** _matrix;
        int * _indegree;
        bool * _visited;
    public:
        G(int n);
        void top_sort();       
};
G::G(int n){
    _node_num = n;
    _matrix = new int* [n];
    _visited = new bool [n];
    _indegree = new int [n];
    for(int i=0; i<n; i++){
        _visited[i] = false;
        _indegree[i] = 0;
        _matrix[i] = new int [n];
        for(int j=0; j<n; j++){ _matrix[i][j]=INF; }
    }
    int m, begin, end;
    cin>>m;
    for(int i=0; i<m; i++){
        cin>>begin>>end;
        begin--;    end--;
        if(_matrix[begin][end]==INF){
            _matrix[begin][end] = 1;
            _indegree[end] ++;
        }
    }
}
void G::top_sort(){
    int i=0; int k=0;
    while(k<_node_num){
        if(_indegree[i]==0 && _visited[i]==false){
            _visited[i] = true; k++;
            cout<<"v"<<i+1;
            if(k!=_node_num)  {cout<<" ";}
            for(int j=0; j<_node_num; j++){
                if(_matrix[i][j]!=INF){
                    _indegree[j]--;
                    _matrix[i][j]=INF;
                }
            }
            i = -1;
        }
        i++;
    }
}
int main(){
    int n;  cin>>n;
    class G graph(n);
    graph.top_sort();
    return 0;
}