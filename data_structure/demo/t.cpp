#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
vector<string> string_split(string s, char split_char);
int main(){
    string s;
    char split_char;
    cin>>s>>split_char;
    vector<string> answer = string_split(s, split_char);
    cout<<answer.size()<<endl;
    for(unsigned int i=0; i<answer.size(); i++)
        cout<<answer[i]<<endl;
    return 0;
}
vector<string> string_split( string s, char split_char){
    vector<string> answer;
    int start=0, length=0;
    while(s[start]!='\0'){
            while(s[start]==split_char && s[start] !='\0')
                start++;
            while(s[start+length]!=split_char && s[start+length]!='\0')
                length++;
            string sub_s = s.substr(start, length);
            if(!sub_s.empty())
                answer.push_back(s.substr(start, length));
            start = start+length+1;
        }
    return answer;
}
