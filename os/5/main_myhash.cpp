#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <sys/time.h>
#include <list>

/* 自己写的hashTable
 */

using namespace std;

const int MAX_PRIME_NUMBER = 2771;
int hash_function(string Key){  //HASH 函数 string转为index
    int sum=0;
    for(int i=0; i<(int)Key.size(); i++){
        int j=1;
        for(int p=0; p<=i; p++,j=j*10);
        sum = j*(int)Key[i]+sum;
    }
    return sum%MAX_PRIME_NUMBER;
}

template<typename Key, typename Value>  //在本题中，我们的Key均为string
class hashtable{
    private:
        vector<vector<Value> > array_value;
        vector<vector<Key> > array_key;
    public:
        hashtable(){
            array_key.resize(MAX_PRIME_NUMBER, vector<Key>(0));
            array_value.resize(MAX_PRIME_NUMBER, vector<Value>(0));
        }
        bool find(Key);
        Value get(Key);
        void erase(Key);
        void insert(Key, Value);
};

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
    for(int num_frame=MIN_NUM_FRAME; num_frame<=MAX_NUM_FRAME; num_frame=num_frame*2){
        int miss_count=0;
        int hit_count=0;
        exec_FIFO_function(filename, num_frame, &miss_count, &hit_count);
        printf("%d\t\t%d\t\t%d\t", num_frame, miss_count, hit_count);
        cout<<setiosflags(ios::fixed)<<setprecision(9)<<(float)miss_count/(miss_count+hit_count)<<endl;
    }
    gettimeofday(&end, 0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("Elapsed of FIFO time is %f sec \n", sec+(usec/1000000.0));

    // Algorithm FIFO
    gettimeofday(&start, 0);
    printf("LRU---\n");
    printf("size\t\tmiss\t\thit\t\tpage fault ratio\n");
    for(int num_frame=MIN_NUM_FRAME; num_frame<=MAX_NUM_FRAME; num_frame=num_frame*2){
        int miss_count=0;
        int hit_count=0;
        exec_LRU_function(filename, num_frame, &miss_count, &hit_count);
        printf("%d\t\t%d\t\t%d\t", num_frame, miss_count, hit_count);
        cout<<setiosflags(ios::fixed)<<setprecision(9)<<(float)miss_count/(miss_count+hit_count)<<endl;
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
    hashtable<string , string > task_map;
    // 初始化busy_page_queue,用于记录在内存中的task。
    queue<string> busy_page_queue;
    // 下一个任务
    while(getline(file, task)){
        task = task.substr(3,5);    //本题中，为了简化起见，忽略操作以及size。
                                    //所以任务取字符串第三位开始,长度为五的字符串。
        //检查当前执行的任务是否在页表里面
        if(task_map.find(task)==false)//任务不在表里
        {
            if((int)busy_page_queue.size()==num_frame)  //页表已经满了
            {
                string str_preDelete = busy_page_queue.front(); //将要被置换任务的地址
                busy_page_queue.pop();
                //task_map.erase(str_preDelete);      //删除
                //cout<<"ERASE"<<str_preDelete<<endl;
                task_map.erase(str_preDelete);
            }
            *miss_count = *miss_count+1;
            //加入map，queue
            task_map.insert(task, task);
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
    hashtable<string ,list<string>::iterator > task_map;
    // 初始化VECTOR, 储存正在内存内的内存地址，用于实现LRU, 最近使用的任务位于VECTOR最前端
    list<string> busy_page_vector;
    while(getline(file, task)){  //若任务队列非空
        task = task.substr(3,5);
        //检查当前执行的任务是否在页表里面
        //如果不在，则将其插入。
        if(task_map.find(task)==false)//任务不在表里
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
            task_map.insert(task, busy_page_vector.begin());
        }else   //任务在表里
        {
            *hit_count = *hit_count+1;
            //更新busy_page_vector
            //查找本次使用的数，删除，并插入VECTOR最前面
            busy_page_vector.erase(task_map.get(task));
            busy_page_vector.push_front(task);
        }
    }
}

template<typename Key, typename Value>
bool hashtable<Key, Value>::find(Key task_str){
    int index = hash_function(task_str);
    for(int i=0; i< (int)array_key[index].size(); i++){
        if(array_key[index][i] == task_str)
            return true;
    }
    return false;
}

template<typename Key, typename Value>
Value hashtable<Key, Value>::get(Key task_str){
    int index = hash_function(task_str);
    for(int i=0; i< (int)array_key[index].size(); i++){
        if(array_key[index][i] == task_str)
            return array_value[index][i];
    }
}

template<typename Key, typename Value>
void hashtable<Key, Value>::erase(Key task_str){
    int index = hash_function(task_str);
    for(int i=0; i< (int)array_key[index].size(); i++){
        if(array_key[index][i] == task_str){
            array_key[index].erase((array_key[index]).begin()+i);
            array_value[index].erase((array_value[index]).begin()+i);
        }
    }
}

template<typename Key, typename Value>
void hashtable<Key, Value>::insert(Key task_str, Value value){
    int index = hash_function(task_str);
    array_key[index].insert(array_key[index].begin(), task_str);
    array_value[index].insert(array_value[index].begin(), value);
}
