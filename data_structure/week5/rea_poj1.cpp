#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

map<string, int> string_2_num;
void init_string();
vector<string> str_split(string s);

int main(){
    init_string();
        string s;
    while(getline(cin, s)){
        int flag=1;
        if(s.size()==0)
            break;

        vector<string > string_arr = str_split(s);
        //have split
        int index = 0; int sum = 0; int temp_sum =0;

        string negative = "negative";
        string million = "million";
        string thousand = "thousand";
        string hundred = "hundred";


        if(string_arr[index]==negative){
            index++;    flag = -1;
        }

        while(index < string_arr.size()){
            string t = string_arr[index];
            if(t == million){
                sum += temp_sum*1000000;
                temp_sum = 0;
            }else if(t == thousand){
                sum += temp_sum*1000;
                temp_sum = 0;
            }else if(t == hundred){
                temp_sum = temp_sum *100;
            }else{
                temp_sum += string_2_num[t];
            }
            index++;
        }
        sum += temp_sum;
        cout<<flag*sum<<endl;
    }
    return 0;
}

vector<string> str_split(string s){
    vector<string > vec_s;
    unsigned int start_index = 0;
    unsigned int length = 0;
    while(start_index<s.size()){
        while(s[start_index+length]!=' '&&start_index+length<s.size())
            length++;
        vec_s.push_back(s.substr(start_index, length));
        start_index = start_index+length+1;
        length = 0;
    }
    return vec_s;
};

void init_string(){
    string_2_num.insert(map<string, int>::value_type("zero", 0));
    string_2_num.insert(map<string, int>::value_type("one", 1));
    string_2_num.insert(map<string, int>::value_type("two", 2));
    string_2_num.insert(map<string, int>::value_type("three", 3));
    string_2_num.insert(map<string, int>::value_type("four", 4));
    string_2_num.insert(map<string, int>::value_type("five", 5));
    string_2_num.insert(map<string, int>::value_type("six", 6));
    string_2_num.insert(map<string, int>::value_type("seven", 7));
    string_2_num.insert(map<string, int>::value_type("eight", 8));
    string_2_num.insert(map<string, int>::value_type("nine", 9));
    string_2_num.insert(map<string, int>::value_type("ten", 10));
    string_2_num.insert(map<string, int>::value_type("eleven", 11));
    string_2_num.insert(map<string, int>::value_type("twelve", 12));
    string_2_num.insert(map<string, int>::value_type("thirteen", 13));
    string_2_num.insert(map<string, int>::value_type("fourteen", 14));
    string_2_num.insert(map<string, int>::value_type("fifteen", 15));
    string_2_num.insert(map<string, int>::value_type("sixteen", 16));
    string_2_num.insert(map<string, int>::value_type("seventeen", 17));
    string_2_num.insert(map<string, int>::value_type("eighteen", 18));
    string_2_num.insert(map<string, int>::value_type("nineteen", 19));
    string_2_num.insert(map<string, int>::value_type("twenty", 20));
    string_2_num.insert(map<string, int>::value_type("thirty", 30));
    string_2_num.insert(map<string, int>::value_type("forty", 40));
    string_2_num.insert(map<string, int>::value_type("fifty", 50));
    string_2_num.insert(map<string, int>::value_type("sixty", 60));
    string_2_num.insert(map<string, int>::value_type("seventy", 70));
    string_2_num.insert(map<string, int>::value_type("eighty", 80));
    string_2_num.insert(map<string, int>::value_type("ninety", 90));
}
