#include<iostream>
#include<string>
#include<cstdio>

using namespace std;


//大整数乘法

void jinWei(int *arr, int index, int number);

int main(){

    //初始化结果数组`
    const int size = 40000;
    int result[size];
    for(int i=0; i<size; i++)
        result[i]=0;
    //
    string a,b;
    cin>>a>>b;
    int temp_result,temp_index;
    for(int i=(int)a.size()-1; i>=0; i--){
        int temp_a=(int)a[i]-'0';
        for(int j=(int)b.size()-1; j>=0; j--){
            int temp_b=(int)b[j]-'0';
            temp_result = temp_a * temp_b;
            temp_index = size-1-(b.size()-1-j)-(a.size()-1-i);
            jinWei(result, temp_index, temp_result);
        }
    }
    //显示结果
    bool tag=false;
    for(int i=0; i<size; i++){
        if(result[i]!=0&&!tag)
            tag = true;
        if(tag)
            cout<<result[i];
    }
    if(!tag)
        cout<<0;
    cout<<endl;
    return 0;

}

void jinWei(int * arr , int index, int number){
    int now = arr[index];
    if(now+number>=10){
        arr[index] = (now+number)%10;
        jinWei(arr, index-1, (now+number)/10);
    }else{
        arr[index] = now+number;
    }
}
