#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define DATATYPE int
#define POSITION int

struct ArgsOfFunction{
    DATATYPE* array;
    POSITION left;
    POSITION right;
    int inter_num;
};
bool SaveArrayToFile(const char *, DATATYPE* , int);
bool Exchange(DATATYPE *, DATATYPE *);
void BubbleSort(DATATYPE *, POSITION, POSITION);
void ShowIntSort(int *, int );
void ExeWithSingleThread(const char *);
void ExeWithMultiThread(const char *);
void* thread_function(void *);
POSITION Partition(DATATYPE *, POSITION left, POSITION right);
DATATYPE* LoadArrayFromFile(const char *, int *);


int main(){
    /*
    pthread_t thread_ID_1, thread_ID_2;
    const char str[10] = "Hellowold";
    int number = 5;
	void * value[2] = {(void *)str, (void *)(&number)};
    void *exit_value;
    int arr[5] = {1,4,6,3,2};
    BubleSort(arr,5);
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
bool Exchange(DATATYPE *left, DATATYPE* right){
    DATATYPE temp = *left;
    *left = *right;
    *right = temp;
    return true;
}
void BubbleSort(DATATYPE * arr, POSITION left, POSITION right){
    DATATYPE temp;
    int length = right-left+1;
    for(POSITION i=left; i<length-1; i++){
        for(POSITION j=right; j<length-1-i; j++){
            if(*(arr+j)>*(arr+j+1)){
                temp = *(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = temp;
            }
        }
    }
}
void ShowIntSort(int *arr, int length){
    for(int i=0; i<length; i++)
        printf("%2d ", *(arr+i));
}
void ExeWithSingleThread(const char * filename){
    int length;
    DATATYPE* array = LoadArrayFromFile(filename, &length);
    clock_t begin_time, end_time;
    begin_time = clock();
    BubbleSort(array,0,length);
    end_time = clock();
    std::cout<<"COMSUMING Time is "<<(double)(end_time-begin_time)/CLOCKS_PER_SEC;
    SaveArrayToFile("output2.txt", array, length);
}
void ExeWithMultiThread(const char * filename){
    int length;

    DATATYPE* array = LoadArrayFromFile(filename, &length);

    struct ArgsOfFunction temp;
    temp.array = array;
    temp.left = 0;
    temp.right = length;
    temp.inter_num = 3;

    clock_t begin_time, end_time;
    begin_time = clock();
    pthread_t thread_ID;
    pthread_create(&thread_ID, NULL, thread_function, &temp);
    end_time = clock();
    std::cout<<"COMSUMING Time is "<<(double)(end_time-begin_time)/CLOCKS_PER_SEC;
    SaveArrayToFile("output2.txt", array, length);
}
void* thread_function(void *args){
    struct ArgsOfFunction * args_value = (struct ArgsOfFunction *)args;
    int int_num = args_value->inter_num;
    if(int_num==0){
        BubbleSort(args_value->array, args_value->left, args_value->right);
        return NULL;
    }else{
        sem_t binary_sem;
        sem_init(&binary_sem, 1);

    }
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

