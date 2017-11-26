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

bool Exchange(DATATYPE *, DATATYPE *);                          //Exchange two element
void BubbleSort(DATATYPE *, POSITION, POSITION);                //底层使用的冒泡排序
void ExeWithMultiThread(DATATYPE * arr, int max_thread_num,
                        POSITION left, POSITION right);         //
POSITION Partition(DATATYPE *, POSITION left, POSITION right);  //查找Partition的函数, flag数是数组最后的一个数
DATATYPE* LoadArrayFromFile(const char *, int *);               //Load array from the file
void WriteArrayToFile(const char *, int *, int );               //Write array to the file
void * thread_function(void *);                                 //线程使用的函数
void exec_function(struct Args_of_task );                      //本题中具体使用的函数
struct Args_of_task GetTaskFromQueue();
void AddTaskToQueue(struct Args_of_task);

// 全局变量
const int MAX_SIZE_OF_THREAD_POOL = 8;      //本题中，线程池中线程的最大数目
const int MAX_DEEP_LAYER=3;                 //本题中，最深的层数，层数从0开始
sem_t sem_arr[MAX_SIZE_OF_THREAD_POOL];     //线程使用的信号量
sem_t sem_mutex;
int num_of_live_thread;                     //正在运行的线程数
int num_deepest;
struct Args_of_thread thread_pool[MAX_SIZE_OF_THREAD_POOL]; //线程池
queue<struct Args_of_task> task_queue;     //初始化任务序列

int main(){
    int length_of_arr;
    string fileName;
    struct timeval start, end;
    int sec=0, usec=0;
    sem_init(&sem_mutex, 0, 0);

    //Input the fileName
    std::cout<<"Please input the name of the file\n";
    //std::cin>>fileName;
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
    for(int max_thread_num=2; max_thread_num<MAX_SIZE_OF_THREAD_POOL; max_thread_num++){
        DATATYPE * arr_multiple = LoadArrayFromFile(fileName.c_str(), &length_of_arr);
        gettimeofday(&start,0);
        ExeWithMultiThread(arr_multiple, max_thread_num, 0, length_of_arr-1);
        gettimeofday(&end,0);
        sec = end.tv_sec-start.tv_sec;
        usec = end.tv_usec-start.tv_usec;
        printf("Elapsed of multiply thread %d is %f sec.\n",max_thread_num, sec+(usec/1000000.0));
        //Save
        char cache[16];
        sprintf(cache, "%d", max_thread_num);
        string order = cache;
        WriteArrayToFile(("output"+order+".txt").c_str(), arr_multiple, length_of_arr);
    }
    return 1;
}
void * thread_function(void * args){
    struct Args_of_thread* args_of_thread = (struct Args_of_thread *)args;
    printf("%d等待\n", args_of_thread->id);
    while(1){
        sem_wait(args_of_thread->sem_id); //进入休眠模式，直到有任务激活
        printf("%d激活\n", args_of_thread->id);
        num_of_live_thread++;
        exec_function(args_of_thread->args_of_function);
        printf("%d结束,再次进入休眠状态\n", args_of_thread->id);
        num_of_live_thread--;
    }
}
bool Exchange(DATATYPE *left_index, DATATYPE* right_index){
    DATATYPE temp = *left_index;
    *left_index = *right_index;
    *right_index = temp;
    return true;
}
void BubbleSort(DATATYPE * arr, POSITION left_index, POSITION right_index){
    struct timeval start, end;
    int sec=0, usec=0;
    gettimeofday(&start,0);
    for(POSITION i=left_index; i<right_index+1; i++){
        for(POSITION j=left_index; j<right_index+1-(i-left_index); j++){
            if(*(arr+j)>*(arr+j+1)){
                Exchange(arr+j, arr+(j+1));
            }
        }
    }

    gettimeofday(&end,0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("%f sec.",sec+(usec/1000000.0));
    printf("%p Left Index is %d, Right Index is %d.\n",arr, left_index, right_index);
}
void ShowIntSort(int *arr, int length){
    printf("Array is:");
    for(int i=0; i<length; i++)
        printf("%2d ", *(arr+i));
    printf("\n");
}
void ShowIntSort(int *arr, int left_index, int right_index){
    printf("Array is:");
    for(int i=left_index; i<right_index+1; i++)
        printf("%2d ", *(arr+i));
    printf("\n");

}
void ExeWithMultiThread(DATATYPE * arr, int max_thread_num,
                        POSITION left_index, POSITION right_index){
    //Init the first task and append it to the task_queue
    num_of_live_thread=0;
    num_deepest=8;
    struct Args_of_task t;

    t.element_arr = arr;
    t.length = right_index-left_index+1;
    t.layer = 0;
    t.task_id = 0;
    AddTaskToQueue(t);

    /*
    while(num_deepest){
        int value;
        sem_getvalue(thread_pool[0].sem_id, &value);
        if(value==0){
            int size = (int)task_queue.size();
            if(size){
                printf("当前任务队列的容量%d\n", size);
                //struct Args_of_task pre_ = task_queue.front();
                //task_queue.pop();
                struct Args_of_task pre_ = GetTaskFromQueue();
                size = (int)task_queue.size();
                printf("当前执行的task，arr is %p, length is %d  \n\
                id is %d layer is %d\n", pre_.element_arr, pre_.length, pre_.task_id, pre_.layer);
                printf("Get task 之后任务队列容量%d\n", size);
                thread_pool[0].args_of_function = pre_;
                sem_post(thread_pool[0].sem_id);
            }
        }
    }*/

    //Start the first task
    while(num_deepest){
        int size = (int)task_queue.size();
        if(size){   //当前任务队列非空
            printf("当前任务队列的容量%d\n", size);
            /*
            struct Args_of_task pre_ = task_queue.front();
            task_queue.pop();
            */
            struct Args_of_task pre_ = GetTaskFromQueue();
            size = (int)task_queue.size();
            printf("当前执行的task，arr is %p, length is %d  \n\
                    id is %d layer is %d\n", pre_.element_arr, pre_.length, pre_.task_id, pre_.layer);
            printf("Get task 之后任务队列容量%d\n", size);
            //Find sleep thread to active
            for(int i=0; ;i++){
                i = i % max_thread_num;
                //printf("Find thread\n");
                int flag; // If flag = 0; Thread is sleep
                sem_getvalue(thread_pool[i].sem_id, &flag);
                if(flag==0){//找到处于休眠模式的进程
                    printf("Flag is %d,thread %d is selected.\n",flag, i);
                    thread_pool[i].args_of_function = pre_;
                    sem_post(thread_pool[i].sem_id);
                    printf("%d is running. 当前的num_deepest 为%d\n", i, num_deepest);
                    break;
                }
            }
        }
        //printf("Loop finished\n");
    };
    printf("当前的num_deepest 为%d\n",  num_deepest);
}
void exec_function(struct Args_of_task  args){
    //init the data;
    DATATYPE * arr = args.element_arr;
    POSITION left = 0;
    POSITION right = args.length-1;
    int layer = args.layer;
    if(args.length==1){
        if(layer==MAX_DEEP_LAYER){
            num_deepest--;
            //Do Nothing
        }else{
            struct Args_of_task arg_left;
            arg_left.element_arr = arr;
            arg_left.length = 1;
            arg_left.layer = layer+1;
            arg_left.task_id = args.task_id*2+1;
            AddTaskToQueue(arg_left);
        }
    }else if(args.length==0){
        if(layer==MAX_DEEP_LAYER)
            num_deepest--;
        //Do Nothing
    }else{
        if(layer==MAX_DEEP_LAYER){
            BubbleSort(arr, left, right);
            num_deepest--;
        }else{
            POSITION p = Partition(arr, left, right);
            printf("%p Left is %d Right is %d P is %d\n",arr, left, right,  p);
            //Product two new task
            struct Args_of_task task_left,task_right;
            task_left.element_arr = arr;
            task_left.length = p;
            task_left.layer = layer+1;
            task_left.task_id = args.task_id*2+1;
            AddTaskToQueue(task_left);
            task_right.element_arr = arr+p;
            task_right.length = right-p+1;
            task_right.layer = layer+1;
            task_right.task_id = args.task_id*2+2;
            AddTaskToQueue(task_right);
            printf("插入任务之后，当前任务容量%d.\n",(int) task_queue.size());
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
    printf("%d\n", *length);
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
    int value;
    sem_getvalue(&sem_mutex, &value);
    struct Args_of_task re;
    while(1){
        if(value==0){       //空闲
            sem_post(&sem_mutex);   //上锁
            re = task_queue.front();
            task_queue.pop();
            sem_wait(&sem_mutex);   //解锁
            break;
        }
        sem_getvalue(&sem_mutex, &value);
    }
    return re;
}

void AddTaskToQueue(struct Args_of_task task){
    int value;
    sem_getvalue(&sem_mutex, &value);
    while(1){
        if(value==0){//空闲
            sem_post(&sem_mutex);   //上锁
            task_queue.push(task);
            sem_wait(&sem_mutex);   //解锁
            break;
        }
        sem_getvalue(&sem_mutex, &value);
    }
}
