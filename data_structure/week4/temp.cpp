#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int main(){
    string a = "asdad";
    string b = "sad";
    b = a;
    char aa[]="adsad";
    cout<<sizeof(aa)/sizeof(char)<<endl;
    cout<<strlen(aa);
    return 1;
}
