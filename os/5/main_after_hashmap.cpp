#include <iostream>
#include <map>          //map,无需加上-std=c++11
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <sys/time.h>
#include <list>

using namespace std;

string address;
const int MIN_NUM_FRAME = 64;
const int MAX_NUM_FRAME = 512;

void exec_FIFO_function(string filename, int num_frame, int * miss_count, int * hit_count);
void exec_LRU_function(string filename, int num_frame, int * miss_count, int * hit_count );


int main(){
    //Cord the time
    struct timeval start,end;
    int sec=0,usec=0;

    //FILE_NAME
    string filename = "trace.txt";
    // Algorithm FIFO
    gettimeofday(&start, 0);
    printf("FIFO---\n");
    printf("size\t\tmiss\t\thit\t\tpage fault ratio\n");
    for(int num_frame=MIN_NUM_FRAME; num_frame<=MAX_NUM_FRAME; num_frame=num_frame*2){
        int miss_count=0;
        int hit_count=0;
        exec_FIFO_function(filename, num_frame, &miss_count, &hit_count);
        printf("%d%12d%12d\t", num_frame, miss_count, hit_count);
        cout<<setiosflags(ios::fixed)<<setprecision(6)<<(float)miss_count/(miss_count+hit_count)<<endl;
    }
    gettimeofday(&end, 0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("Elapsed of FIFO time is %f sec \n", sec+(usec/1000000.0));

    // Algorithm FIFO
    gettimeofday(&start, 0);
    printf("LRU---\n");
    printf("size        miss        hit         page fault ratio\n");
    for(int num_frame=MIN_NUM_FRAME; num_frame<=MAX_NUM_FRAME; num_frame=num_frame*2){
        int miss_count=0;
        int hit_count=0;
        exec_LRU_function(filename, num_frame, &miss_count, &hit_count);
        printf("%d%12d%12d%18f\n", num_frame, miss_count, hit_count, ((float)miss_count)/(miss_count+hit_count));

    }
    gettimeofday(&end, 0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("Elapsed of LRU time is %f sec \n", sec+(usec/1000000.0));


}

void exec_FIFO_function(string filename, int num_frame, int* miss_count, int* hit_count){
    ifstream file(filename.c_str());
    string task;
    // 初始化hash_map,用于实现查找 key 是address，value是string
    map<string , string > task_map;
    // 初始化busy_page_queue,用于记录在内存中的task。
    queue<string> busy_page_queue;
    // 下一个任务
    while(getline(file, task)){
        task = task.substr(3,5);    //本题中，为了简化起见，忽略操作以及size。
                                    //所以任务取字符串第三位开始,长度为五的字符串。
        //检查当前执行的任务是否在页表里面
        if(task_map.find(task)==task_map.end())//任务不在表里
        {
            if((int)busy_page_queue.size()==num_frame)  //页表已经满了
            {
                string str_preDelete = busy_page_queue.front(); //将要被置换任务的地址
                busy_page_queue.pop();
                //task_map.erase(str_preDelete);      //删除
                //cout<<"ERASE"<<str_preDelete<<endl;
                task_map.erase(task_map.find(str_preDelete));
            }
            *miss_count = *miss_count+1;
            //加入map，queue
            task_map.insert(make_pair(task, task));
            busy_page_queue.push(task);
        }else   //任务在表里
        {
            *hit_count = *hit_count+1;
        }
    }
}

void exec_LRU_function(string filename, int num_frame, int* miss_count, int* hit_count){

    ifstream file(filename.c_str());
    string task;
    // 初始化hash_map,用于实现查找 key 是address，value是vector<string>迭代器
    map<string ,list<string>::iterator > task_map;
    // 初始化VECTOR, 储存正在内存内的内存地址，用于实现LRU, 最近使用的任务位于VECTOR最前端
    list<string> busy_page_vector;
    while(getline(file, task)){  //若任务队列非空
        task = task.substr(3,5);
        //检查当前执行的任务是否在页表里面
        //如果不在，则将其插入。
        if(task_map.find(task)==task_map.end())//任务不在表里
        {
            if((int)busy_page_vector.size()==num_frame)  //页表已经满了
            {
                string str_preDelete = busy_page_vector.back(); //将要被置换任务的地址
                busy_page_vector.pop_back();
                task_map.erase(str_preDelete);      //删除
            }
            *miss_count = *miss_count+1;
            //加入map，vector
            busy_page_vector.insert(busy_page_vector.begin(),task);
            task_map.insert(make_pair(task, busy_page_vector.begin()));
        }else   //任务在表里
        {
            *hit_count = *hit_count+1;
            //更新busy_page_vector
            //查找本次使用的数，删除，并插入VECTOR最前面
            busy_page_vector.erase(task_map[task]);
            busy_page_vector.push_front(task);
        }
    }
}
