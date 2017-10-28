#include <iostream>
#include <semaphore.h>

sem_t binary_sem;

int main(){
    sem_init(&binary_sem,0, 0);
    sem_wait(&binary_sem);
    int result;
    sem_getvalue(&binary_sem, &result);
    std::cout<<result;
}
