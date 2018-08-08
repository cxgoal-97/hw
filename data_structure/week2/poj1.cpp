#include<iostream>
#include<vector>

using namespace std;
//约瑟夫问题
//
//
int main(){
    //n是编号，ｍ是退出的数
    unsigned int n=0,m=0;
    cin>>n>>m;
    vector<unsigned int> array_monkey;
    //初始化
    for(unsigned int i=0; i<n; i++)
        array_monkey.push_back(i+1);
    //开始删除
    unsigned int number =1;   //当前报号
    int index_num =0;   //当前下标
    while(array_monkey.size()!=1){
        if(number==m){
            array_monkey.erase(array_monkey.begin()+index_num);
            number=1;
        }else{
            index_num++;
            number++;
        }
        if((unsigned int)index_num>=array_monkey.size())
            index_num =0;
    }
    cout<<array_monkey[0];
    return 0;
}
