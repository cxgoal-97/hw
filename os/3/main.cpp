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
void ShowIntSort(int *, int , int );
void ExeWithSingleThread(DATATYPE * arr, POSITION left, POSITION right, int inter_num);
void ExeWithMultiThread(DATATYPE * arr, POSITION left, POSITION right, int inter_num);
void* thread_function(void *);
POSITION Partition(DATATYPE *, POSITION left, POSITION right);
DATATYPE* LoadArrayFromFile(const char *, int *);

using std::string;

int main(){
    string fileName = "txt";
    int length_of_arr;
    DATATYPE * arr = LoadArrayFromFile(fileName.c_str(), &length_of_arr);
    ShowIntSort(arr, 0, length_of_arr-1);
    ExeWithSingleThread(arr, 0, length_of_arr-1, 1);
    ShowIntSort(arr, 0, length_of_arr-1);
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
    DATATYPE temp;
    for(POSITION i=left_index; i<right_index+1; i++){
        for(POSITION j=left_index; j<right_index+1-i; j++){
            if(*(arr+j)>*(arr+j+1)){
                Exchange(arr+j, arr+(j+1));
            }
        }
    }
    ShowIntSort(arr,left_index, right_index);
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
void ExeWithMultiThread(DATATYPE * arr, POSITION left, POSITION right, int inter_num){
    int length;


    struct ArgsOfFunction temp;
    temp.left = 0;
    temp.inter_num = 3;

    clock_t begin_time, end_time;
    begin_time = clock();
    pthread_t thread_ID;
    pthread_create(&thread_ID, NULL, thread_function, &temp);
    end_time = clock();
    std::cout<<"COMSUMING Time is "<<(double)(end_time-begin_time)/CLOCKS_PER_SEC;
}
void* thread_function(void *args){
    struct ArgsOfFunction * args_value = (struct ArgsOfFunction *)args;
    int int_num = args_value->inter_num;
    if(int_num==0){
        BubbleSort(args_value->array, args_value->left, args_value->right);
        return NULL;
    }else{
        sem_t binary_sem;
        sem_init(&binary_sem,0,1);
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

