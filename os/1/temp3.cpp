#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using std::string;
using std::cin;
using std::cout;

int main(){
    // fork
    pid_t pid = fork();

    if(pid < 0){
        fprintf(stderr, "Fork Failed.\n");
        exit(-1);
    }else if(pid == 0 ){    //child process
        exit(0);
    }else{  //parent process
        wait();
        printf("Child Complete.\n");
    }

    char* argv[] = {"cat","temp.cpp",(char*)NULL};
    execv("/bin/cat",argv);


    string in_string;
    cin>>in_string;
    string c="213";
    printf("%s",c.c_str());
    return 0;
}
