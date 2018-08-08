#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;
struct node{
    int xishu;
    int zhishu;
};

void add();

int main(){
    int n;
    cin>>n;
    while(n--){
        add();
    }
}


void add(){
    vector<int> xishu_array;
    vector<int> zhishu_array;

    int xishu,zhishu;

    for(int i=0; i<2; i++){
    scanf("%d%d",&xishu,&zhishu);
    while(zhishu>=0){

        //cout<<"读入的系数指数分别为"<<xishu<<"  "<<zhishu<<endl;
        //查找，
        unsigned int index= 0;
        for(index=0; index<zhishu_array.size(); index++){
            if(zhishu_array[index]==zhishu){
                xishu_array[index]= xishu_array[index]+xishu;
                break;
            }
            if(zhishu_array[index]<zhishu){
                xishu_array.insert(xishu_array.begin()+index, xishu);
                zhishu_array.insert(zhishu_array.begin()+index, zhishu);
                break;
            }
        }
        //index == zhishu_array.size(),没有找到
        if(index==zhishu_array.size()){
            xishu_array.push_back(xishu);
            zhishu_array.push_back(zhishu);
        }
        scanf("%d%d",&xishu,&zhishu);
    }
    }
    for(unsigned int index=0; index<xishu_array.size(); index++){
        if(xishu_array[index]!=0)
            cout<<"[ "<<xishu_array[index]<<" "<<zhishu_array[index]<<" ] ";
    }
    cout<<endl;
}
