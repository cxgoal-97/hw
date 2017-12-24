#include<unistd.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>
#include<cstring>
#include<string>

using namespace std;

int main(){
    struct timeval start,end;
    int sec=0, usec=0;
    gettimeofday(&start,0);
    string temp = "temp.txt";

    //FILE * temp_pointer= fopen("temp.txt", "at+");
    for(int j=0; j<400; j++){

        FILE * file_pointer = fopen("largefile.txt", "at+");

        for(int i=0; i<4096; i++){
            //fwrite(a, sizeof(char), 50, file_pointer);
            fprintf(file_pointer, "%d", 1);

        }
        //
        //
        //fsync(fd);
        //fflush(file_pointer);
        //
        fclose(file_pointer);
        //
        //fclose(file_pointer);
        char buffer[256];
        sprintf(buffer, "%d", j);
        string number = buffer;
        number = number+temp;
        FILE * temp_pointer= fopen(number.c_str(), "w");
        //fd2 = fileno(temp_pointer)
        for(int i=0; i<2; i++){
            //fwrite(a, sizeof(char), 2050, temp_pointer);
            fprintf(temp_pointer, "%d", 1);
        }

        //fflush(temp_pointer);
        //fsync(fd2);
        fclose(temp_pointer);
        number = "filefrag -v "+number;
        sync();
        system(number.c_str());
        //number = "rm "+number;
        //system(number.c_str());

    }
    //fclose(temp_pointer);
    sync();
    system("filefrag -v largefile.txt");
    gettimeofday(&end,0);
    sec = end.tv_sec-start.tv_sec;
    usec = end.tv_usec-start.tv_usec;
    std::cout<<"Time is"<<sec+(usec/1000000.0);
    //system("rm largefile.txt temp.txt");
    return 1;
}
