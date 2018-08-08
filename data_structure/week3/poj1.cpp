#include<iostream>
#include<string>

using namespace std;
void enCode();

int main(){
    int n;
    cin>>n;
    string cache;
    getline(cin, cache);
    while(n--){
        enCode();
    }
    return 1;
}

void enCode(){
    string str;
    getline(cin, str);
    for(unsigned int i=0; i<str.size(); i++){
        if((('a'<=str[i])&&(str[i]<'z'))||(('A'<=str[i])&&(str[i]<'Z')))
            cout<<(char)(str[i]+1);
        else if(str[i]=='z')
            cout<<'a';
        else if(str[i]=='Z')
            cout<<'A';
        else
            cout<<str[i];
    }
    cout<<endl;
}
