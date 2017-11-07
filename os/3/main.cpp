#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <semaphore.h>
#include <time.h>

#define DATATYPE int
#define POSITION int

struct Array{
    DATATYPE* array;
    POSITION left;
    POSITION right;
};
struct Args_of_function{
    struct Array ** arr_of_struct;
    int thread_num;
};

bool SaveArrayToFile(const char *, DATATYPE* , int);
bool Exchange(DATATYPE *, DATATYPE *);
void BubbleSort(DATATYPE *, POSITION, POSITION);
void ShowIntSort(int *, int );
void ShowIntSort(int *, int , int );
void ExeWithSingleThread(DATATYPE * arr, POSITION left, POSITION right, int inter_num);
void ExeWithMultiThread(DATATYPE * arr, POSITION left, POSITION right);
void* thread_function(void *);
POSITION Partition(DATATYPE *, POSITION left, POSITION right);
DATATYPE* LoadArrayFromFile(const char *, int *);

using std::string;

sem_t sem_main;
sem_t sem_arr[16];
int thread_pool_num = 15;

int main(){
    string fileName = "txt";
    int length_of_arr;
    DATATYPE * arr = LoadArrayFromFile(fileName.c_str(), &length_of_arr);
    ShowIntSort(arr, 0, length_of_arr-1);
    ExeWithSingleThread(arr, 0, length_of_arr-1, 1);
    ShowIntSort(arr, 0, length_of_arr-1);
    ExeWithMultiThread(arr, 0, length_of_arr-1);
    /*
    pthread_t thread_ID_1, thread_ID_2;
    const char str[10] = "Hellowold";
    int number = 5;
	void * value[2] = {(void *)str, (void *)(&number)};
    void *exit_value;
    int arr[5] = {1,4,6,3,2};
    BubbleSort(arr,5);
    ShowIntSort(arr,5);
    pthread_create(&thread_ID_1, NULL, thread_function, value);
    pthread_create(&thread_ID_2, NULL, thread_function, value);
    pthread_join(thread_ID_1, &exit_value);
    */
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
    for(POSITION i=left_index; i<right_index+1; i++){
        for(POSITION j=left_index; j<right_index+1-i; j++){
            if(*(arr+j)>*(arr+j+1)){
                Exchange(arr+j, arr+(j+1));
            }
        }
    }
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
        BubbleSort(arr, left_index, right_index);
    }else{
        POSITION pivot = Partition(arr, left_index, right_index);
        ExeWithSingleThread(arr, left_index, pivot, inter_num-1);
        ExeWithSingleThread(arr, pivot+1, right_index, inter_num-1);
    }
}
void ExeWithMultiThread(DATATYPE * arr, POSITION left_index, POSITION right_index){
    //init the sem
    sem_init(&sem_main, 0, 0);
    for(int i=0; i<15; i++)
        sem_init(sem_arr+i, 0, 0);
    //init the args
    struct Array * array_of_arr[15];
    for(int i=0; i<15; i++){
        array_of_arr[i] = (struct Array* ) new struct Array;
        array_of_arr[i]->array = arr;
        array_of_arr[i]->right = right_index;
        array_of_arr[i]->left = left_index;
    }
    struct Args_of_function arrOfArgsOfFunction[15];
    for(int i=0; i<15; i++){
        arrOfArgsOfFunction[i].arr_of_struct = array_of_arr;
        arrOfArgsOfFunction[i].thread_num = i;
    }
    //init the pthread
    pthread_t p_id[15];
    for(int i=0; i<15; i++)
        pthread_create(p_id+i, NULL, thread_function, (void *)(arrOfArgsOfFunction+i));
    sem_post(sem_arr+0);
    sem_wait(&sem_main);
}
void * thread_function(void * args){
    //init the data;
    struct Args_of_function * args_of_thread = (struct Args_of_function *) args;
    int thread_num = args_of_thread->thread_num;
    struct Array* arr = *((struct Array**)(args_of_thread->arr_of_struct)+thread_num);
    //block until the signal
    sem_wait(sem_arr+thread_num);

    if(thread_num>=7&&thread_num<=14)
        BubbleSort(arr->array, arr->left, arr->right);
    else{
        POSITION p = Partition(arr->array, arr->left, arr->right);
        int thread_num_l = thread_num*2+1;
        int thread_num_r = thread_num*2+2;
        std::cout<<thread_num_l<<"     "<<thread_num_r<<"\n";
        ((struct Array *)(args_of_thread->arr_of_struct)+thread_num_l)->right = p;
        ((struct Array *)(args_of_thread->arr_of_struct)+thread_num_r)->left = p;
        sem_post(sem_arr+thread_num_r);
        sem_post(sem_arr+thread_num_l);
    }
    std::cout<<"Thread num is"<<thread_num<<std::endl;
    if((--thread_pool_num)==0)
        sem_post(&sem_main);
}


POSITION Partition(DATATYPE *arr, POSITION left, POSITION right) {
    DATATYPE pivot = *(arr+right);
    POSITION i = left;
    POSITION j = left;
    while (j < right) {
        if (*(arr + j) < pivot) {
            Exchange(arr+i, arr+j);
            i++;
        }
        j++;
    }
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

