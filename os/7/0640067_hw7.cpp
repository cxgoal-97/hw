#include<unistd.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>
#include<cstring>
#include<string>

using namespace std;

int main(int argc, char **argv){
    if(argc!=2){
        cout<<argv[1];
        return 0;
    }
    string path_all = argv[1];
    //检查path_all 末尾是否有/，如果有就去掉
    if(path_all[path_all.size()-1]=='/'){
        path_all = path_all.substr(0, path_all.length()-1);
    }


    struct timeval start,end;
    int sec=0, usec=0;
    gettimeofday(&start,0);
    string temp = "temp.txt";

    int loop_t = 1;
    int size = 1024*1024;
    int a = 1; int tag = 0;
    char buffer[256];
    for(int j=0; ; j++){
        sprintf(buffer, "%d", j);
        string number = buffer;

        number = path_all+'/'+number+temp;
        FILE * file_pointer = fopen(number.c_str(), "w");
        if(file_pointer == NULL){
            cout<<"创建文件失败，请检查权限\n";
            return 0;
        }

        for(int i=0; i<loop_t; i++){
            if(fwrite(&a, sizeof(a), size, file_pointer)==0){
                tag = 1;
                break;
            }
        }

        if(tag)
            break;
        fclose(file_pointer);
    }
    sync();

    tag =0;
    for(int j=1;j<2000 ; j = j+2){
        sprintf(buffer, "%d", j);
        string number = buffer;
        number = path_all+'/'+number+temp;
        /*小文件大小要求是powers of 2
        if(j==1)
            system(("ls -l "+ number).c_str());
        */
        remove(number.c_str());


        string output_file = path_all+'/'+"largefile.txt";
        FILE * file_pointer = fopen(output_file.c_str(), "a+");
        for(int i=0; i<j%10; i++){
            if(fwrite(&a, sizeof(a), size, file_pointer)==0){
                tag = 1;
                //cout<<"已满"<<endl;
                break;
            }
        }

        if(tag)
            break;
        //fsync(fileno(file_pointer));
        //fflush(file_pointer);
        fclose(file_pointer);
    }


    /*
     *
     *
    system("rm *9temp.txt");
    */

    sync();
    string delete_path = "rm "+path_all+"/*temp.txt";
    system(delete_path.c_str());
    string show_answer = "filefrag -v "+path_all+"/largefile.txt";
    system(show_answer.c_str());
    //fclose(temp_pointer);
    gettimeofday(&end,0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    std::cout<<"Time is"<<sec+(usec/1000000.0);
    //system("rm largefile.txt temp.txt");
    return 1;
}
