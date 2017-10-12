#include <iostream>
#include <stdio.h>
#include <unistd.h>     //sleep, pipe, dup2
#include <stdlib.h>     //exit, malloc
#include <vector>       //vector
#include <string.h>     //string
#include <sys/wait.h>   //wait()
#include <sys/stat.h>   //open S开头的宏文件
#include <fcntl.h>      //open O开头的常量

using std::string;
using std::cin;
using std::cout;
using std::vector;

vector<string> split (string str);      //将字符串按照空格进行分割
bool normal_execv (string in_string);   //正常的命令执行
bool redirect_execv (string in_string); //重定向的实现
bool pipe_execv (string in_string);     //pipe的实现

int main(){

    printf(">");
    string in_string;
    //读入含空格的一句话
    getline(cin,in_string);
    //输入Exit,就退出
    while(in_string!="Exit"){
        pid_t pid = fork();
        if(pid < 0){            //failing
            fprintf(stderr, "Fork Failed.\n");
            exit(-1);
        }else if(pid == 0 ){    //child process

            //I/O Redirection
            if(in_string.find(">")!=in_string.npos){
                //cout<<"Redirection\n";
                if(!redirect_execv(in_string)){
                    printf("Error\n");
                    exit(-1);
                }
            }else if(in_string.find("|")!=in_string.npos){
                //cout<<"Pipe\n";
                if(!pipe_execv(in_string)){
                    printf("Error\n");
                    exit(-1);
                }
            }else{
                //cout<<"Normal\n";
                if(!normal_execv(in_string)){
                    printf("Error\n");
                    exit(-1);
                }
            }
        }else{  // parent process
            wait(NULL);
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
        if(p_after<size && in_string[p_after]!=' '){
            string s = in_string.substr(p_before, 1+p_after-p_before);
            result.push_back(s);
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

    // aim_order 重定向的目标
    // 去除>后面的空格
    while(in_string[pos+1]==' ')
        pos++;
    string aim_order = in_string.substr(pos+1,in_string.size()-(1+pos));

    int out;
    out = open(aim_order.c_str(), O_WRONLY | O_TRUNC |O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    /*
     * O_WRONLY 写文件， O_TRUNC 若文件存在，清空，属性不变，O_CREAT 若文件不存在，新建文件。
     * S_IRUSR 拥有者有读权限， S_IRGRP 组内成员读权限， S_IWGRP 组内成员写权限， S_IWUSR 拥有者有权限。
     */

    dup2(out,1);
    close(out);
    if(!normal_execv(pre_order))
        return false;
    return true;
}

bool pipe_execv(string in_string){
    if(in_string.find("|")==in_string.npos)
        return normal_execv(in_string);
    else{
        string::size_type pos = in_string.find("|");
        string pre_order = in_string.substr(0,pos);
        string aim_order = in_string.substr(pos+1,in_string.size()-pos);
        int pipefd[2];
        pipe(pipefd);
        pid_t pid = fork();
        // 选择父进程或者子进程作为输入会导致不同的结果
        /*
        if(pid ==0){    //child
            dup2(pipefd[0],0);
            close(pipefd[1]);
            if(!pipe_execv(aim_order))
                return false;
        }else{  //parent
            dup2(pipefd[1],1);
            close(pipefd[0]);
            if(!normal_execv(pre_order))
                return false;
        }
        */
        if(pid ==0){    //child
            dup2(pipefd[1],1);
            close(pipefd[0]);
            if(!normal_execv(pre_order))
                return false;
        }else{  //parent
            dup2(pipefd[0],0);
            close(pipefd[1]);
            if(!pipe_execv(aim_order))
                return false;
        }
    }
    return true;
}
