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


#define DATATYPE int
#define POSITION int

struct Args_of_function{
    DATATYPE * element_arr;
    POSITION * length;
    int thread_num;
};

bool SaveArrayToFile(const char *, DATATYPE* , int);
bool Exchange(DATATYPE *, DATATYPE *);
void BubbleSort(DATATYPE *, POSITION, POSITION);
void BubbleSort(DATATYPE * , int );
void ShowIntSort(int *, int );
void ShowIntSort(int *, int , int );
void ExeWithSingleThread(DATATYPE * arr, POSITION left, POSITION right, int inter_num);
void ExeWithMultiThread(DATATYPE * arr, POSITION left, POSITION right);
void* thread_function(void *);
POSITION Partition(DATATYPE *, POSITION left, POSITION right);
DATATYPE* LoadArrayFromFile(const char *, int *);
void WriteArrayToFile(const char *, int *, int );

int comp(const void *a, const void *b){ return (*(int *)a-*(int *)b);};
using std::string;

// 全局变量
sem_t sem_arr[16];
sem_t sem_main;
struct Args_of_function args_arr[15];
int length[15];


int main(){
    int length_of_arr;
    string fileName;
    struct timeval start, end;
    int sec=0, usec=0;

    std::cout<<"Please input the name of the file\n";
    std::cin>>fileName;

    DATATYPE * arr_single = LoadArrayFromFile(fileName.c_str(), &length_of_arr);
    DATATYPE * arr_multiple = LoadArrayFromFile(fileName.c_str(), &length_of_arr);

    //Single Thread
    gettimeofday(&start,0);
    ExeWithSingleThread(arr_single, 0, length_of_arr-1, 3);
    gettimeofday(&end,0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("Elapsed of single thread is %f sec.\n",sec+(usec/1000000.0));
    //Multiply Thread
    gettimeofday(&start,0);
    ExeWithMultiThread(arr_multiple, 0, length_of_arr-1);
    gettimeofday(&end,0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("Elapsed of multiply thread is %f sec.\n",sec+(usec/1000000.0));
    //ShowIntSort(arr_multiple, 0, length_of_arr-1);
    // Check the result of two ways is same
    int tag=0;
    for (int i=0; i<length_of_arr; i++){
        if(*(arr_single+i)!=*(arr_multiple+i)){
            printf("Different id is %d\n",i);
            tag=1;
        }
    }

    printf("Right tag is %d ", tag);
    WriteArrayToFile("output1.txt", arr_single, length_of_arr);
    WriteArrayToFile("output2.txt", arr_multiple, length_of_arr);
    return 1;
}
bool SaveArrayToFile(const char * filename, DATATYPE* array, int length){
    std::fstream file;
    file.open(filename,std::ios::out);
    for(int i=0; i<length; i++){
        file<<*(i+array)<<" ";
        std::cout<<*(i+array);
    }
    file.close();
    return true;
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
    printf("Left Index is %d, Right Index is %d.\n", left_index, right_index);
}


void BubbleSort(DATATYPE * arr, int length){
    struct timeval start, end;
    int sec=0, usec=0;
    gettimeofday(&start,0);
    for(POSITION i=0; i<length; i++){
        for(POSITION j=0; j<length-i; j++){
            if(*(arr+j)>*(arr+j+1)){
                Exchange(arr+j, arr+(j+1));
            }
        }
    }
    gettimeofday(&end,0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    printf("%p %f  sec. Length %d",arr,sec+(usec/1000000.0),length);
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
void ExeWithSingleThread(DATATYPE * arr, POSITION left_index, POSITION right_index, int inter_num){
    if(inter_num==0){
        //printf("L %6d R  %6d\n", left_index, right_index);
        BubbleSort(arr, left_index, right_index);
    }else{
        //printf("L %6d R  %6d\n", left_index, right_index);
        if(right_index>left_index){
            POSITION pivot = Partition(arr, left_index, right_index);
            ExeWithSingleThread(arr, left_index, pivot-1, inter_num-1);
            ExeWithSingleThread(arr, pivot, right_index, inter_num-1);
        }
    }
}
void ExeWithMultiThread(DATATYPE * arr, POSITION left_index, POSITION right_index){
    //init the sem
    sem_init(&sem_main, 0, 0);
    for(int i=0; i<15; i++)
        sem_init(sem_arr+i, 0, 0);
    length[0] = right_index-left_index+1;

    for(int i=0; i<15; i++){
        args_arr[i].element_arr = arr;
        args_arr[i].length = length;
        args_arr[i].thread_num = i;
    }
    //init the pthread
    pthread_t p_id[15];
    for(int i=0; i<15; i++)
        pthread_create(p_id+i, NULL, thread_function, (void *)(args_arr+i));
    sem_post(sem_arr+0);
    //printf("Multiply Thread start.\n");
    sem_wait(&sem_main);
}
void * thread_function(void * args){
    //init the data;
    struct Args_of_function * args_of_thread = (struct Args_of_function *) args;
    int thread_num = args_of_thread->thread_num;
    //block until the signal
    sem_wait(sem_arr+thread_num);

    DATATYPE * arr = args_of_thread->element_arr;
    POSITION left = 0;
    POSITION right = args_of_thread->length[thread_num]-1;
    if(args_of_thread->length[thread_num]==1){
        if(thread_num>=7&&thread_num<=14){
            sem_post(sem_arr+0);
        }else{
            int thread_num_l = thread_num*2+1;
            int thread_num_r = thread_num*2+2;

            args_arr[thread_num_l].element_arr = arr;
            (args_of_thread->length)[thread_num_l]= 1;

            (args_of_thread->length)[thread_num_r]= 0;

            sem_post(sem_arr+thread_num_l);
            sem_post(sem_arr+thread_num_r);
            printf("\n");
        }
    }else if(args_of_thread->length[thread_num]==0){
        if(thread_num>=7&&thread_num<=14){
            sem_post(sem_arr+0);
        }else{
            int thread_num_l = thread_num*2+1;
            int thread_num_r = thread_num*2+2;

            (args_of_thread->length)[thread_num_l]= 0;

            (args_of_thread->length)[thread_num_r]= 0;

            sem_post(sem_arr+thread_num_l);
            sem_post(sem_arr+thread_num_r);
            printf("\n");
        }
    }else{
        if(thread_num>=7&&thread_num<=14){
            BubbleSort(arr, left, right);
            sem_post(sem_arr+0);
        }else{
            POSITION p = Partition(arr, left, right);
            printf("%p Left is %d Right is %d P is %d\n",arr, left, right,  p);
            int thread_num_l = thread_num*2+1;
            int thread_num_r = thread_num*2+2;

            args_arr[thread_num_l].element_arr = arr;
            (args_of_thread->length)[thread_num_l]= p;

            args_arr[thread_num_r].element_arr = arr+p;
            (args_of_thread->length)[thread_num_r]= right-p+1;

            sem_post(sem_arr+thread_num_r);
            sem_post(sem_arr+thread_num_l);
            printf("\n");
        }
    }
    if(thread_num==0){  //T1等待所有的底层线程
        for(int i=0; i<8; i++)
            sem_wait(sem_arr+0);
        sem_post(&sem_main);
    }
    printf("T%d is finished Left is %d Right is %d\n", thread_num, left ,right);
    //std::cout<<"Thread num is"<<thread_num<<std::endl;
    return NULL;
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

