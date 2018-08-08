#include <iostream>
#include <cstdio>

// dfs 
using namespace std;
const int MAX_SIZE = 200;

class MAP{
    private:
        int _min_step;
        int _up_wall[MAX_SIZE][MAX_SIZE];  // 0 代表有墙，1代表可以过去,-1代表出去是外面
        int _down_wall[MAX_SIZE][MAX_SIZE];
        int _left_wall[MAX_SIZE][MAX_SIZE];
        int _right_wall[MAX_SIZE][MAX_SIZE];
        int visited[MAX_SIZE][MAX_SIZE];
    public:
        void dfs(double x, double y, int step_num);
        void init(){
            _min_step = -1;
            for(int i=0; i<MAX_SIZE; i++){
                for(int j=0; j<MAX_SIZE; j++){
                    _up_wall[i][j] = _down_wall[i][j] = _left_wall[i][j] = _right_wall[i][j] = -1;
                    visited[i][j] = 0;
                }
            }
        }
        void add_wall(int start_x, int start_y, int tag , int length);
        void add_door(int start_x, int start_y, int tag);
        int get_ans()   {return _min_step;}
};


int main(){
    int M,N;
    cin>>M>>N;
    class MAP map;
    while(M!=-1 && N!=-1){
        map.init();
        int tx, ty, t_tag, t_length;
        for(int i=0; i<M; i++){
            cin>>tx>>ty>>t_tag>>t_length;
            map.add_wall(tx, ty, t_tag, t_length);
        }
        for(int i=0; i<N; i++){
            cin>>tx>>ty>>t_tag;
            map.add_door(tx, ty, t_tag);
        }
        double start_x, start_y;
        cin>>start_x>>start_y;
        //map.dfs(start_x, start_y, 0);
        cout<<map.get_ans();
        cin>>M>>N;
    }
    return 0;
}

void MAP::add_wall(int start_x, int start_y, int tag, int length){
    // tag 0 代表X,1代表 Y
    if(tag==0){
        for(int i=0; i<length; i++){
            _up_wall[start_x+i][start_y-1] = 0;
            _down_wall[start_x+i][start_y] = 0;
        }
    }else{
        for(int i=0; i<length; i++){
            _left_wall[start_x][start_y+i] = 0;
            _right_wall[start_x-1][start_y+i] = 0;
        }
    }
}

void MAP::add_door(int start_x, int start_y, int tag){
    // tag 0 代表X, 1代表Y
    if(tag==0){
        _up_wall[start_x][start_y-1] = 1;
        _down_wall[start_x][start_y] = 1;
    }else{
        _left_wall[start_x][start_y] = 1;
        _right_wall[start_x-1][start_y]  = 1;
    }
}

void MAP::dfs(double x, double y, int step_num){
    int low_left_x = int(x);    int low_left_y = int(y);
    if(low_left_x==0||low_left_y==0||low_left_x==MAX_SIZE-1||low_left_y==MAX_SIZE-1){
        if(_min_step !=-1)
            _min_step = min(_min_step, step_num);
        else
            _min_step = step_num;
        return ;
    }else if(_up_wall[low_left_x][low_left_y]==-1||_down_wall[low_left_x][low_left_y]==-1||
            _left_wall[low_left_x][low_left_y]==-1||_right_wall[low_left_x][low_left_y]==-1){
        _min_step = min(_min_step, step_num);
        return ;
    }else if(visited[low_left_x][low_left_y]!=1){   //未被访问过
        if(_up_wall[low_left_x][low_left_y]==1){
            dfs(x, y+1, step_num+1);
            cout<<low_left_x<<"  "<<low_left_y<<"上移动\n";
        }else if(_down_wall[low_left_x][low_left_y]==1){
            dfs(x, y-1, step_num+1);
            cout<<low_left_x<<"  "<<low_left_y<<"下移动\n";
        }else if(_left_wall[low_left_x][low_left_y]==1){
            dfs(x-1, y, step_num+1);
            cout<<low_left_x<<"  "<<low_left_y<<"左移动\n";
        }else if(_right_wall[low_left_x][low_left_y]==1){
            dfs(x+1, y, step_num+1);
            cout<<low_left_x<<"  "<<low_left_y<<"右移动\n";
        }
        visited[low_left_x][low_left_y] = 1;
    }
}