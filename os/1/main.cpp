#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <sys/wait.h>

using std::string;
using std::cin;
using std::cout;
using std::vector;

vector<string> split (string str, string pattern);

int main(){
    // fork
    printf("<");
    string in_string;
    getline(cin,in_string);

    while(in_string!="Exit"){

        pid_t pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork Failed.\n");
            exit(-1);
        }else if(pid == 0 ){    //child process
            vector<string> result = split(in_string," ");
            const char** argv =(const char **)malloc(((int)result.size()+1)*sizeof(char *));
            for(int i = 0; i<(int)result.size(); i++)
                argv[i] = result[i].c_str();
            argv[(int)result.size()+1] = (char *)NULL;

            string path = "/bin/"+result[0];
            if(execv(path.c_str(), (char* const*)argv)<0){
                cout<<"ERROR！\n";
                exit(-1);
                }
            exit(0);
            }
        else{  //parent process
            wait(NULL);
            printf("<");
            getline(cin,in_string);
        }
    }

    return 0;
}

vector<string> split (string str, string pattern){
    string::size_type pos;
    vector<string> result;
    str += pattern;
    int size = str.size();

    for(int i=0; i<size; i++){
        pos = str.find(pattern,i);
        if((int)pos<size){
            string s = str.substr(i,pos-i);
            result.push_back(s);
            i = pos+pattern.size()-1;
        }
    }
    return result;
}
