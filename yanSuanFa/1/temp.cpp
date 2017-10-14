#include <fstream>
#include <iostream>
#include <stdio.h>

int main(){
    std::ifstream file;
    file.open("data/50000data.txt");
    char output[100];
    file>>output;
    std::cout<<"is "<<output;
    file>>output;
    file.close();
    return 0;
}


