#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <sys/wait.h>

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::string;
using std::cin;
using std::cout;
using std::vector;

vector<string> split (string str);
bool normal_execv (string in_string);
bool redirect_execv (string in_string);
bool pipe_execv (string in_string);

int main(){
    // fork
    ///*
    printf(">");
    string in_string;
    getline(cin,in_string);

    while(in_string!="Exit"){

        pid_t pid = fork();
        if(pid < 0){
            fprintf(stderr, "Fork Failed.\n");
            exit(-1);
        }else if(pid == 0 ){    //child process
            //I/O Redirection
            if(in_string.find(">")!=in_string.npos){
                //cout<<"Redirection\n";
                if(redirect_execv(in_string)==false){
                    printf("Error\n");
                    exit(-1);
                }
            }else if(in_string.find("|")!=in_string.npos){
                //cout<<"Pipe\n";
                if(pipe_execv(in_string)==false){
                    printf("Error\n");
                    exit(-1);
                }
            }else{
                //cout<<"Normal\n";
                if(normal_execv(in_string)==false){
                    printf("Error\n");
                    exit(-1);
                }
            }
        }else{
            wait(NULL);
            sleep(1);
            printf(">");
            getline(cin,in_string);

        }

    }
    //*/
    return 0;
}

vector<string> split (string in_string){
    vector<string> result;
    int size = in_string.size();
    int p_before = 0, p_after = 0;
    while(p_before<size){
        while(in_string[p_before]==' '&&(1+p_before)<size)
            p_before++;
        p_after = p_before;
        while(in_string[p_after+1]!=' '&&(1+p_after)<size){
            p_after++;
        }
        //cout<<"p_after"<<p_after<<"\n";
        if(p_after<size && in_string[p_after]!=' '){
            string s = in_string.substr(p_before, 1+p_after-p_before);
            result.push_back(s);
            //cout<<"p_before is"<<p_before<<"p_after is"<<p_after<<"\n";
            //cout<<"s is "<<s<<"\n";
        }
        p_before = p_after+1;
    }
    return result;
}

bool normal_execv(string in_string){

    vector<string> result = split(in_string);
    const char** argv =(const char **)malloc(((int)result.size()+1)*sizeof(char *));
    for(int i = 0; i<(int)result.size(); i++)
        argv[i] = result[i].c_str();
    argv[(int)result.size()+1] = (char *)NULL;
    if(execvp(result[0].c_str(),(char* const*)argv)<0){
        return false;
    }
    return true;
}

bool redirect_execv(string in_string){
    string::size_type pos = in_string.find(">");
    string pre_order = in_string.substr(0,pos);

    // 重定向的目标
    // 去除>后面的空格
    while(in_string[pos+1]==' ')
        pos++;
    string aim_order = in_string.substr(pos+1,in_string.size()-(1+pos));
    cout<<aim_order<<"\n";
    int out;
    out = open(aim_order.c_str(), O_WRONLY | O_TRUNC |O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    dup2(out,1);
    close(out);
    if(normal_execv(pre_order)==false)
        return false;
    return true;
}

bool pipe_execv(string in_string){
    string::size_type pos = in_string.find("|");
    string pre_order = in_string.substr(0,pos);

    string aim_order = in_string.substr(pos+1,in_string.size()-pos);

    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();
    if(pid ==0){
        dup2(pipefd[0],0);
        close(pipefd[1]);
        if(normal_execv(aim_order)==false)
            return false;
    }else{
        dup2(pipefd[1],1);
        close(pipefd[0]);
        if(normal_execv(pre_order)==false)
            return false;
    }
    return true;
}
