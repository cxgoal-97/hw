#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

bool is_number(string s);
bool is_unit(string s);
int unit_to_number(string s);
int number_to_number(string s);
bool is_bigger(string s1, string s2);       //s1 < s2 为真
vector<string> split(string s, char split_flag);


int main(){
    string s;
    int negative_flag;
    int answer;
    vector<string> vector_s;
    string max = "hundred\0";

    while(getline(cin, s)){
        if(s==" ")
            break;
        else{
            answer = 0;
            negative_flag = 1;
            vector_s.clear();
            vector_s = split(s,' ');
            unsigned int p=0;
            if(vector_s[0]=="negative"){
                p++;negative_flag = -1;
            }

            while(p<vector_s.size()){
                if(is_number(vector_s[p])){ //如果是数字
                    if(p==vector_s.size()-1){
                        answer += number_to_number(vector_s[p]);
                        // cout<< number_to_number(vector_s[p])<<endl;
                        break;
                    }
                    //检查后一位是否为单位
                    if(is_unit(vector_s[p+1])){//如果是单位
                        if(is_bigger(vector_s[p+1], max)){  //如果单位小
                            answer += number_to_number(vector_s[p])*unit_to_number(vector_s[p+1]);
                            //cout<< number_to_number(vector_s[p])*unit_to_number(vector_s[p+1])<<endl;
                            p = p+2;
                        }else{
                            answer = (answer+number_to_number(vector_s[p]))*unit_to_number(vector_s[p+1]);
                            //cout<< number_to_number(vector_s[p])*unit_to_number(vector_s[p+1])<<endl;
                            p = p+2;
                            max = vector_s[p+1];
                        }
                    }else{
                        answer += number_to_number(vector_s[p]);
                        //cout<< number_to_number(vector_s[p])<<endl;
                        p = p+1;
                    }
                }
            }
            cout<<negative_flag*answer<<endl;
        }
    }
    return 0;
}

bool is_bigger(string s1, string s2){   //s1<s2
    if(s1=="hundred")
        return true;
    if(s1=="thousand" && s2!="hundred")
        return true;
    if(s1=="million")
        return false;
    return false;
}

vector<string> split(string s, char split_flag){
    vector<string> vector_s;
    unsigned int start=0;
    unsigned int length=0;

    while(start<s.size()){
        length=0;
        while(s[start]==split_flag&& s[start+1]!='\0')
            start++;
        while(s[start+length]!=split_flag&& s[start+length]!='\0')
            length++;
        vector_s.push_back(s.substr(start, length));
        start = start + length +1;
    }

    return vector_s;
}


bool is_unit(string s){
    if(s=="hundred"||s=="thousand"||s=="million")
        return true;
    return false;
}

bool is_number(string s){
    if(s=="zero"||s=="one"||s=="two"||s=="three")
        return true;
    if(s=="four"||s=="five"||s=="six"||s=="seven")
        return true;
    if(s=="eight"||s=="nine"||s=="ten"||s=="eleven")
        return true;
    if(s=="twelve"||s=="thirteen"||s=="fourteen")
        return true;
    if(s=="fifteen"||s=="sixteen"||s=="seventeen")
        return true;
    if(s=="eighteen"||s=="nineteen")
        return true;
    if(s=="twenty"||s=="thirty"||s=="forty")
        return true;
    if(s=="fifty"||s=="sixty"||s=="seventy")
        return true;
    if(s=="eighty"||s=="ninety")
        return true;
    return false;
}

int unit_to_number(string s){
    if(s=="hundred")
        return 100;
    if(s=="thousand")
        return 1000;
    if(s=="million")
        return 1000000;
    return -1;
}

int number_to_number(string s){
    if(s=="zero")
        return 0;
    if(s=="one")
        return 1;
    if(s=="two")
        return 2;
    if(s=="three")
        return 3;
    if(s=="four")
        return 4;
    if(s=="five")
        return 5;
    if(s=="six")
        return 6;
    if(s=="seven")
        return 7;
    if(s=="eight")
        return 8;
    if(s=="nine")
        return 9;
    if(s=="ten")
        return 10;
    if(s=="eleven")
        return 11;
    if(s=="twelve")
        return 12;
    if(s=="thirteen")
        return 13;
    if(s=="fourteen")
        return 14;
    if(s=="fifteen")
        return 15;
    if(s=="sixteen")
        return 16;
    if(s=="seventeen")
        return 17;
    if(s=="eighteen")
        return 18;
    if(s=="nineteen")
        return 19;
    if(s=="twenty")
        return 20;
    if(s=="thirty")
        return 30;
    if(s=="forty")
        return 40;
    if(s=="fifty")
        return 50;
    if(s=="sixty")
        return 60;
    if(s=="seventy")
        return 70;
    if(s=="eighty")
        return 80;
    if(s=="ninety")
        return 90;
    return -1;
}

