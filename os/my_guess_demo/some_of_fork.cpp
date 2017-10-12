#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int a = 0;
    pid_t pid = fork();
    /* fork 函数在父进程和子进程中均返回，一次调用两次返回
     * 对于父进程， fork 返回子进程的pid
     * 对于子进程， fork 返回0
     */
    if(pid>0){
        // wait(NULL);
        a++ ;
        std::cout<<"Parent"<<a<<std::endl;
        std::cout<<"a is "<<a<<" and the address is"<<&a<<std::endl;
    }else{
        a = 5;
        std::cout<<"Child"<<a<<std::endl;
        std::cout<<"a is "<<a<<" and the address is"<<&a<<std::endl;

    }
}
