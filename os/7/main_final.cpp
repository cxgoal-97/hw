#include<unistd.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>
#include<cstring>
#include<string>

using namespace std;

int main(){
    string path_all;
    printf("请输入挂载的地址\n");
    cin>>path_all;

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

        for(int i=0; i<loop_t; i++){
            if(fwrite(&a, sizeof(a), size, file_pointer)==0){
                tag = 1;
                cout<<"已满"<<endl;
                break;
            }
        }
        loop_t++;
        if(loop_t==10)
            loop_t = 1;

        if(tag)
            break;
        //fsync(fileno(file_pointer));
        //fflush(file_pointer);
        fclose(file_pointer);
        //number = "rm "+number;
        //system(number.c_str());
        cout<<"当前循环"<<j<<endl;
    }
    sync();



    /*
    for(int i=0; i<300; i++){
        if(fwrite(&a, sizeof(a), size, file_pointer)==0){
            tag = 1;
            cout<<"已满"<<endl;
            break;
        }
    }
    //fsync(fileno(file_pointer));
    fclose(file_pointer);
    //fclose(file_pointer);
    //sync();
    //number = "rm "+number;
    //system(number.c_str());


    sync();
    system("filefrag -v largefile.txt");
    */

    tag =0;
    for(int j=1;j<2000 ; j = j+2){
        sprintf(buffer, "%d", j);
        string number = buffer;
        number = path_all+'/'+number+temp;
        remove(number.c_str());


        string output_file = path_all+'/'+"largefile.txt";
        FILE * file_pointer = fopen(output_file.c_str(), "a+");
        for(int i=0; i<j%10; i++){
            if(fwrite(&a, sizeof(a), size, file_pointer)==0){
                tag = 1;
                cout<<"已满"<<endl;
                break;
            }
        }

        if(tag)
            break;
        //fsync(fileno(file_pointer));
        //fflush(file_pointer);
        fclose(file_pointer);
        //number = "rm "+number;
        //system(number.c_str());
        cout<<"largefile当前循环"<<j<<endl;
    }


    /*
     *
     *
    system("rm *9temp.txt");
    */
    /*
    tag = 0;
    for(int j=0;j<200 ; j++){

        FILE * file_pointer = fopen("largefile.txt", "a+");

        if(file_pointer==NULL)
            break;
        for(int i=0; i<2; i++){
            if(fwrite(&a, sizeof(a), size, file_pointer)==0){
                tag = 1;
                cout<<"已满"<<endl;
                break;
            }
        }
        if(tag)
            break;
        //fsync(fileno(file_pointer));
        fclose(file_pointer);
        //fclose(file_pointer);
        //sync();
        //number = "rm "+number;
        //system(number.c_str());

    }

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
