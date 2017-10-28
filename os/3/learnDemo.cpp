#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define DATATYPE int

DATATYPE* LoadArrayFromFile(const char *);
bool SaveArrayToFile(const char *);
DATATYPE GetPivot(DATATYPE * );
DATATYPE SortByPivot(DATATYPE *, DATATYPE);
void BubleSort(DATATYPE *, int );
void ShowIntSort(int *, int );

void* thread_function1(void *arg){
    sleep(2);
    printf("Function1 and vualue is %d \n",*(int *)(arg));
    (*(int *)(arg))--;
    return NULL;
}

void* thread_function2(void *arg){
    sleep(1);
    printf("Function2 and vualue is %d",*(int *)(arg));
    (*(int *)(arg))++;
    return NULL;
}
int main(){
    pthread_t thread_ID_1, thread_ID_2;
    int value = 5;
    void *exit_value;
    int arr[5] = {1,4,6,3,2};
    BubleSort(arr,5);
    ShowIntSort(arr,5);
    pthread_create(&thread_ID_1, NULL, thread_function1,&value );
    pthread_create(&thread_ID_2, NULL, thread_function2,&value );
    pthread_join(thread_ID_1, &exit_value);
}

void BubleSort(DATATYPE * arr, int length){
    DATATYPE temp;
    for(int i=0; i<length-1; i++){
        for(int j=0; j<length-1-i; j++){
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
