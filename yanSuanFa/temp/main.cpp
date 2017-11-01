#include<iostream>

void DrawZ(int size);
void DrawA(int size);
void DrawX(int size);
void DrawV(int size);
void DrawN(int size);

using namespace std;

int main(){
    int size;
    cin>>size;
    DrawZ(size);
    DrawX(size);
    DrawV(size);
    DrawN(size);
    DrawA(size);
    return 0;
}


void DrawN(int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(j==0||j==size-1||j==i)
                cout<<"*";
            else
                cout<<" ";
        }
        cout<<endl;
    }
}

void DrawV(int size){
    for(int i=0; i<size; i=i+2){
        for(int j=0; j<size; j++){
           if(j==i/2||j==size-1-i/2)
                cout<<"*";
           else
                cout<<" ";
        }
        cout<<endl;
        cout<<endl;
    }
}

void DrawX(int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(j==i||j==size-i-1)
                cout<<"*";
            else
                cout<<" ";
        }
        cout<<endl;
    }
}

void DrawA(int size){
    int bar = size/3*2;
    for(int i=0; i<size; i=i+2){
        for(int j=0; j<size; j++){
            if(j==size/2-i/2||j==size/2+i/2)
                cout<<"*";
            else if(i==bar&&(j>size/2-i/2&&j<size/2+i/2))
                cout<<"*";
            else
                cout<<" ";
        }
        cout<<endl;
        cout<<endl;
    }
}

void DrawZ(int size){
    for(int i=0; i<size; i++)
        cout<<"*";
    cout<<endl;
    for(int i=1; i<size-1; i++){
        for(int j=0; j<size; j++){
            if(j!=size-1-i)
                cout<<" ";
            else
                cout<<"*";
        }
        cout<<endl;
    }
    for(int i=0; i<size; i++)
        cout<<"*";
    cout<<endl;
}
