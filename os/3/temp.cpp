#include <iostream>
#include <semaphore.h>
#include <pthread.h>


sem_t sem_arr[2];
sem_t sem_main;

struct sem_num{
    sem_t sem;
    int number;
};
struct sem_num * sem_s;
void* thread_function(void * sem_struct){
    std::cout<<"eheh\n";
    sem_s = (struct sem_num *) sem_struct;
    sem_wait(&(sem_s->sem));
    std::cout<<"A is "<<sem_s->number;
    if(sem_s->number==1234)
        sem_post(&sem_main);
    return NULL;
}
int main(){
    sem_init(&sem_main, 0, -1);
    for(int i=0; i<2; i++)
        sem_init(sem_arr+i, 0, -1);
    pthread_t thread_id1;
    struct sem_num temp = {sem_arr[0],1};
    pthread_create(&thread_id1, NULL, thread_function, (void*)(&temp));
    temp.number = 1234;
    sem_post(&(temp.sem));
    sem_wait(&sem_main);

}
