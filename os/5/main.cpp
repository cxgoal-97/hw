#include <iostream>
#include <map>          //map实现
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Task{
    char op;
    string address;
    int size;
};

const int PAGESIZE = 4096;
const int MIN_NUM_FRAME = 64;
const int MAX_NUM_FRAME = 256;

queue<struct Task> load_task_fromFile(string filename);
void exec_FIFO_function(queue<struct Task> task_queue, int num_frame, int * miss_count, int * hit_count);
void exec_LRU_function(queue<struct Task> task_queue, int num_frame, int * miss_count, int * hit_count );


int main(){
    //FILE_NAME
    string filename = "trace.txt";
    // Algorithm FIFO
    printf("FIFO---\n");
    printf("size        miss        hit         page fault ratio\n");
    for(int num_frame=MIN_NUM_FRAME; num_frame<=MAX_NUM_FRAME; num_frame=num_frame*2){
        int miss_count=0;
        int hit_count=0;
        queue<struct Task> task_queue = load_task_fromFile(filename);
        exec_FIFO_function(task_queue, num_frame, &miss_count, &hit_count);
        printf("%d%12d%12d%18.9f\n", num_frame, miss_count, hit_count, ((float)miss_count)/(miss_count+hit_count));

    }
    // Algorithm FIFO
    printf("LRU---\n");
    printf("size        miss        hit         page fault ratio\n");
    for(int num_frame=MIN_NUM_FRAME; num_frame<=MAX_NUM_FRAME; num_frame=num_frame*2){
        int miss_count=0;
        int hit_count=0;
        queue<struct Task> task_queue = load_task_fromFile(filename);
        exec_LRU_function(task_queue, num_frame, &miss_count, &hit_count);
        printf("%d%12d%12d%18.9f\n", num_frame, miss_count, hit_count, ((float)miss_count)/(miss_count+hit_count));

    }

}

queue<struct Task> load_task_fromFile(string filename){
    queue<struct Task>task_queue;
    ifstream file(filename.c_str());
    char cache[64];
    int p=0;
    while(!file.eof()){     //判断是否到文件尾部
        file>>cache;
        //cout<<"操作"<<cache[0]<<endl;
        char op=cache[0];
        file>>cache;
        string str = cache;
        //cout<<"地址";
        while(cache[++p]!=',');
        string address = str.substr(0, p);
        //cout<<"大小"<<cache[++p];
        int size = (int)cache[++p];
        struct Task new_task ={op, address, size};
        p=0;
        //cout<<"操作"<<new_task.op<<"地址"<<new_task.address<<"大小"<<new_task.size<<endl;
        task_queue.push(new_task);
    }
    return task_queue;
}

void exec_FIFO_function(queue<struct Task> task_queue, int num_frame, int* miss_count, int* hit_count){
    // 初始化hash_map,用于实现查找 key 是address，value是struct Task
    map<string , struct Task> task_map;
    // 初始化队列，储存正在内存内的内存地址，用于实现FIFO
    queue<string> busy_page_queue;
    while(!task_queue.empty()){  //若任务队列非空
        //获取下一个要执行的任务，并将其从任务队列中删除
        struct Task next_task = task_queue.front();
        task_queue.pop();
        //检查当前执行的任务是否在页表里面
        //如果不在，则将其插入。
        string temp_str = next_task.address.substr(0,5);
        if(task_map.find(temp_str)==task_map.end())//任务不在表里
        {
            if((int)busy_page_queue.size()==num_frame)  //页表已经满了
            {
                string str_preDelete = busy_page_queue.front(); //将要被置换任务的地址
                busy_page_queue.pop();
                task_map.erase(str_preDelete);      //删除
            }
            *miss_count = *miss_count+1;
            //加入map，queue
            task_map.insert(map<string, struct Task>::value_type(temp_str, next_task));
            busy_page_queue.push(temp_str);
        }else   //任务在表里
        {
            *hit_count = *hit_count+1;
        }
    }
}

void exec_LRU_function(queue<struct Task> task_queue, int num_frame, int* miss_count, int* hit_count){
    // 初始化hash_map,用于实现查找 key 是address，value是struct Task
    map<string , struct Task> task_map;
    // 初始化VECTOR, 储存正在内存内的内存地址，用于实现LRU, 最近使用的任务位于VECTOR最前端
    vector<string> busy_page_vector;
    while(!task_queue.empty()){  //若任务队列非空
        //获取下一个要执行的任务，并将其从任务队列中删除
        struct Task next_task = task_queue.front();
        task_queue.pop();
        //检查当前执行的任务是否在页表里面
        //如果不在，则将其插入。
        string temp_str = next_task.address.substr(0,5);
        if(task_map.find(temp_str)==task_map.end())//任务不在表里
        {
            if((int)busy_page_vector.size()==num_frame)  //页表已经满了
            {
                string str_preDelete = busy_page_vector.back(); //将要被置换任务的地址
                busy_page_vector.pop_back();
                task_map.erase(str_preDelete);      //删除
            }
            *miss_count = *miss_count+1;
            //加入map，queue
            task_map.insert(map<string, struct Task>::value_type(temp_str, next_task));
            busy_page_vector.insert(busy_page_vector.begin(),temp_str);
        }else   //任务在表里
        {
            *hit_count = *hit_count+1;
            //更新busy_page_vector
            //查找最近使用的数，删除，并插入VECTOR最前面
            int index;
            for(index=0; index<(int)busy_page_vector.size(); index++){
                if(temp_str==busy_page_vector[index])
                    break;
            }
            busy_page_vector.erase(busy_page_vector.begin()+index);
            busy_page_vector.insert(busy_page_vector.begin(), temp_str);
        }
    }
}
