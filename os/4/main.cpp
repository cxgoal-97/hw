/*
#                       _oo0oo_
#                      o8888888o
#                      88" . "88
#                      (| -_- |)
#                      0\  =  /0
#                    ___/`---'\___
#                  .' \\|     |# '.
#                 / \\|||  :  |||# \
#                / _||||| -:- |||||- \
#               |   | \\\  -  #/ |   |
#               | \_|  ''\---/''  |_/ |
#               \  .-\__  '-'  ___/-. /
#             ___'. .'  /--.--\  `. .'___
#          ."" '<  `.___\_<|>_/___.' >' "".
#         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
#         \  \ `_.   \_ __\ /__ _/   .-` /  /
#     =====`-.____`.___ \_____/___.-`___.-'=====
#                       `=---='
#
#
#     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#               佛祖保佑         永无BUG
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <semaphore.h>
#include <cstdlib>
#include <sys/time.h>
#include <queue>


#define DATATYPE int
#define POSITION int

using std::string;
using std::queue;

struct Args_of_task{             //任务参数的结构体,也是具体任务
    DATATYPE * element_arr;
    POSITION  length;
    int layer;
    int task_id;
};

struct Args_of_thread{
    //void (*function_of_thread)(void *args);
    struct Args_of_task args_of_function;
    sem_t* sem_id;
    int id;
};

class Benaphore_Lock {
    public:
        Benaphore_Lock() : counter_(0) {
            sem_init(&semaphore_, 0, 0);
        }
        ~Benaphore_Lock() {
            sem_destroy(&semaphore_);
        }
        void lock(){
            if (__sync_add_and_fetch(&counter_, 1) > 1) {
                sem_wait(&semaphore_);
            }
        }
        void unlock() {
            if(__sync_sub_and_fetch(&counter_, 1) > 0) {
                sem_post(&semaphore_);
            }
        }
        bool TryLock() {
            return __sync_bool_compare_and_swap(&counter_, 0, 1);
        }
    private:
        long counter_;
        sem_t semaphore_;
};
bool Exchange(DATATYPE *, DATATYPE *);                          //Exchange two element
void BubbleSort(DATATYPE *, POSITION, POSITION);                //底层使用的冒泡排序
void ExeWithMultiThread(DATATYPE * arr, int max_thread_num,
                        POSITION left, POSITION right);         //
POSITION Partition(DATATYPE *, POSITION left, POSITION right);  //查找Partition的函数, flag数是数组最后的一个数
DATATYPE* LoadArrayFromFile(const char *, int *);               //Load array from the file
void WriteArrayToFile(const char *, int *, int );               //Write array to the file
void * thread_function(void *);                                 //线程使用的函数
void exec_function(struct Args_of_task );                      //本题中具体使用的函数
struct Args_of_task GetTaskFromQueue();                         //从任务队列中获得任务
void AddTaskToQueue(struct Args_of_task);                       //添加任务到任务队列中
int GetSizeOfQueue();                                           //获得当前任务队列的大小
int GetIdFromQueue();                                           //从线程队列中获得线程id
void AddIdToQueue(int id);                                            //添加线程id到线程队列中
int GetSizeOfThreadIdPool();                                    //获得线程队列的大小

// 全局变量
const int MAX_SIZE_OF_THREAD_POOL = 8;      //本题中，线程池中线程的最大数目
const int MAX_DEEP_LAYER=3;                 //本题中，最深的层数，层数从0开始
sem_t sem_arr[MAX_SIZE_OF_THREAD_POOL];     //线程使用的信号量
class Benaphore_Lock mtx4Task;              //用于任务序列操作的锁
class Benaphore_Lock mtx4Thread;           //用于线程操作的锁
int num_deepest;                            //底层任务完成情况的记录
struct Args_of_thread thread_pool[MAX_SIZE_OF_THREAD_POOL]; //线程池
queue<struct Args_of_task> task_queue;     //初始化任务序列
queue<int> thread_id_pool;

int main(){
    int length_of_arr;
    string fileName;
    struct timeval start, end;
    int sec=0, usec=0;

    //Input the fileName
    std::cout<<"Please input the name of the file\n";
    //std::cin>>fileName;
    //fileName = "data_500000";
    fileName = "input.txt";
    //Init the thread pool
    pthread_t p_id[MAX_SIZE_OF_THREAD_POOL];
    for(int i=0; i<MAX_SIZE_OF_THREAD_POOL; i++){
        sem_init(sem_arr+i, 0, 0);
        thread_pool[i].sem_id = sem_arr+i;
        thread_pool[i].id = i;
        //arr_args[i].function_of_thread = NULL;
        //thread_pool[i].args_of_function = NULL;
        pthread_create(p_id+i, NULL, thread_function, (void *)(thread_pool+i));
    }
    //Multiply Thread
    for(int max_thread_num=1; max_thread_num<=MAX_SIZE_OF_THREAD_POOL; max_thread_num++){
        DATATYPE * arr_multiple = LoadArrayFromFile(fileName.c_str(), &length_of_arr);
        gettimeofday(&start,0);
        ExeWithMultiThread(arr_multiple, max_thread_num, 0, length_of_arr-1);
        gettimeofday(&end,0);
        sec = end.tv_sec-start.tv_sec;
        usec = end.tv_usec-start.tv_usec;
        printf("Elapsed of multiply thread %d is %f ms.\n",max_thread_num, sec*1000+(usec/1000.0));
        //Save
        char cache[16];
        sprintf(cache, "%d", max_thread_num);
        string order = cache;
        WriteArrayToFile(("output"+order+".txt").c_str(), arr_multiple, length_of_arr);
        //清空当前进程id池
        while(thread_id_pool.size()!=0)
            thread_id_pool.pop();

        //检查语句
        /*
        int tag=0;
        for(int i=0; i<length_of_arr-1; i++){
            if(*(arr_multiple+i)>*(arr_multiple+i+1)){
                tag=1;
                printf("%d\n", i);
            }
        }
        if(tag)
            printf("Not AC\n");
        else
            printf("AC\n");
        */
    }
    return 1;
}
void * thread_function(void * args){
    struct Args_of_thread* args_of_thread = (struct Args_of_thread *)args;
    //printf("%d等待\n", args_of_thread->id);
    while(1){
        sem_wait(args_of_thread->sem_id); //进入休眠模式，直到有任务激活
        //printf("线程%d激活, 执行Id 为%d\n", args_of_thread->id, args_of_thread->args_of_function.task_id);
        exec_function(args_of_thread->args_of_function);
        //printf("线程%d结束,再次进入休眠状态\n", args_of_thread->id);
        //将线程id返回到线程中
        AddIdToQueue(args_of_thread->id);
    }
}
bool Exchange(DATATYPE *left_index, DATATYPE* right_index){
    DATATYPE temp = *left_index;
    *left_index = *right_index;
    *right_index = temp;
    return true;
}
void BubbleSort(DATATYPE * arr, POSITION left_index, POSITION right_index){
    //struct timeval start, end;
    //int sec=0, usec=0;
    //gettimeofday(&start,0);
    for(POSITION i=left_index; i<right_index; i++){
        for(POSITION j=left_index; j<right_index-(i-left_index); j++){
            if(*(arr+j)>*(arr+j+1)){
                Exchange(arr+j, arr+(j+1));
            }
        }
    }
}

void ExeWithMultiThread(DATATYPE * arr, int max_thread_num,
                        POSITION left_index, POSITION right_index){
    //Init the first task and append it to the task_queue
    num_deepest=8;
    struct Args_of_task t;

    t.element_arr = arr;
    t.length = right_index-left_index+1;
    t.layer = 0;
    t.task_id = 0;
    AddTaskToQueue(t);

    //将所需要的线程加入进去
    for(int i=0; i<max_thread_num; i++){
        thread_id_pool.push(i);
    }
    int size;       //用于存放任务队列的容量
    while(num_deepest){
        size = GetSizeOfQueue();
        if(size){   //当前任务队列非空
            //printf("当前任务队列的容量%d\n", size);
            struct Args_of_task pre_ = GetTaskFromQueue();
            size = GetSizeOfQueue();
            /*
            printf("当前执行的task，arr is %p, length is %d  \n\
                    id is %d layer is %d\n", pre_.element_arr, pre_.length, pre_.task_id, pre_.layer);
            printf("把任务拿走后任务队列容量%d\n", size);
            */
            //Find sleep thread to active
            while(GetSizeOfThreadIdPool()==0);
            int now_id = GetIdFromQueue();
            thread_pool[now_id].args_of_function = pre_;
            sem_post(thread_pool[now_id].sem_id);
        }
        //printf("Loop finished\n");
    };
}
void exec_function(struct Args_of_task  args){
    //init the data;
    DATATYPE * arr = args.element_arr;
    POSITION left = 0;
    POSITION right = args.length-1;
    int layer = args.layer;
    int id = args.task_id;

    if(right==0){
        if(layer==MAX_DEEP_LAYER){
            __sync_fetch_and_sub(&num_deepest, 1);  //原子操作，对num_deepest-1
            //printf("当前的num_deepest 为%d\n",  num_deepest);
            //Do Nothing
        }else{
            struct Args_of_task task_left, task_right;
            task_left.element_arr = arr;
            task_left.length = 1;
            task_left.layer = layer+1;
            task_left.task_id = id*2+1;
            task_right.length = 0;
            task_right.task_id = id*2+2;
            AddTaskToQueue(task_left);
            AddTaskToQueue(task_right);
        }
    }else if(right==-1){
        if(layer==MAX_DEEP_LAYER)
            __sync_fetch_and_sub(&num_deepest, 1);
            //printf("当前的num_deepest 为%d\n",  num_deepest);
        else{
            struct Args_of_task task_left, task_right;
            task_left.length = 0;
            task_left.task_id = id*2+1;
            task_right.length = 0;
            task_right.task_id = id*2+2;
            AddTaskToQueue(task_left);
            AddTaskToQueue(task_right);
        }
        //Do Nothing
    }else{
        if(layer==MAX_DEEP_LAYER){
            //printf("对ID%d 进行排序\n", id);
            BubbleSort(arr, left, right);
            __sync_fetch_and_sub(&num_deepest, 1);
            //printf("当前的num_deepest 为%d\n",  num_deepest);
        }else{
            POSITION p = Partition(arr, left, right);
            /*
            printf("id %d Partition部分结束  \n \
                    %p Left is %d Right is %d P is %d\n",id ,arr, left, right,  p);
            */
            //Product two new task
            struct Args_of_task task_left,task_right;
            task_left.element_arr = arr;
            task_left.length = p;
            task_left.layer = layer+1;
            task_left.task_id = id*2+1;
            task_right.element_arr = arr+p;
            task_right.length = right-p+1;
            task_right.layer = layer+1;
            task_right.task_id = id*2+2;
            AddTaskToQueue(task_left);
            AddTaskToQueue(task_right);
            /*
            printf("添加的任务 %p, 长度为 %d, id为 %d, 层数 %d\n", task_left.element_arr, task_left.length, task_left.task_id, task_left.layer);
            printf("添加的任务 %p, 长度为 %d, id为 %d, 层数 %d\n", task_right.element_arr, task_right.length, task_right.task_id, task_right.layer);
            */
        }
    }
}

POSITION Partition(DATATYPE *arr, POSITION left, POSITION right) {
    DATATYPE pivot = *(arr+right);
    POSITION i = left-1;
    POSITION j = left;
    while (j < right) {
        if (*(arr + j) <= pivot) {
            i++;
            Exchange(arr+i, arr+j);
        }
        j++;
    }
    i++;
    Exchange(arr+i, arr+right);
    return i;
}
DATATYPE* LoadArrayFromFile(const char * filename, int * length){
    std::fstream file;
    file.open(filename);
    char buffer[64];
    file>>buffer;
    sscanf(buffer, "%d", length);
    DATATYPE * array = (DATATYPE *) new DATATYPE[*length];
    for(int i=0; i<*length; i++){
        file>>buffer;
        sscanf(buffer, "%d", array+i);
    }
    //printf("%d\n", *length);
    file.close();
    return array;
}
void WriteArrayToFile(const char * filename, int * array, int length){
    std::ofstream file;
    file.open(filename);
    for(int i=0; i<length; i++){
        file<<*(array+i);
        if(i!=length-1)
            file<<" ";
    }
    file.close();
}

struct Args_of_task GetTaskFromQueue(){
    struct Args_of_task re;
    mtx4Task.lock();
    //printf("正在获取任务, 对任务操作上锁.\n");
    re = task_queue.front();
    task_queue.pop();
    //printf("获取任务id%d ,对任务操作解锁\n", re.task_id);
    mtx4Task.unlock();
    return re;
}

void AddTaskToQueue(struct Args_of_task task){
    mtx4Task.lock();
    //printf("正在添加任务%d, 对任务操作上锁\n", task.task_id);
    task_queue.push(task);
    //printf("任务添加结束,对任务操作解锁\n");
    mtx4Task.unlock();
}

int GetSizeOfQueue(){
    mtx4Task.lock();
    int size = (int)task_queue.size();
    mtx4Task.unlock();
    return size;
}

int GetSizeOfThreadIdPool(){
    mtx4Thread.lock();
    int size = (int)thread_id_pool.size();
    mtx4Thread.unlock();
    return size;
}

void AddIdToQueue(int id){
    mtx4Thread.lock();
    thread_id_pool.push(id);
    //printf("ID %d 线程被加入至闲置线程\n", id);
    mtx4Thread.unlock();
}

int GetIdFromQueue(){
    mtx4Thread.lock();
    int id = thread_id_pool.front();
    thread_id_pool.pop();
    //printf("ID %d 线程被用于执行任务\n", id);
    mtx4Thread.unlock();
    return id;
}
