#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int x = 0;

int main(){
    // fork
    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "Fork Failed.\n");
        exit(-1);
    }else if(pid == 0 ){    //child process
        x++;
        printf("%d",x);
        exit(0);
    }else{  //parent process
        wait();
        printf("%d",x);
        exit(0);
    }
    return 0;
}
