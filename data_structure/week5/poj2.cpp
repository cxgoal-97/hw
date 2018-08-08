#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main(){
    vector<string> str_dic;
    string in_str;
    //读入字典
    while(cin>>in_str,in_str!="#"){
        str_dic.push_back(in_str);
    };
    //读入待查词
    while(cin>>in_str,in_str!="#"){
        //检查是否完全匹配
        bool success_tag = false;
        for(unsigned int i=0; i<str_dic.size(); i++){
            if(in_str.size()==str_dic[i].size()){
                unsigned int j=0;
                while(in_str[j]==str_dic[i][j]&&j<in_str.size())
                    j++;
                if(j==in_str.size()){
                    cout<<in_str<<" is correct\n";
                    success_tag = true;
                    break;
                }
            }
        }
        if(success_tag!=true){  //若未能完全匹配
            cout<<in_str<<":";
            for(unsigned int i=0; i<str_dic.size(); i++){
                //
                //替换字母
                if(in_str.size()==str_dic[i].size()){
                    unsigned int j=0,p=0;
                    while(j<in_str.size()){
                        if(in_str[j]==str_dic[i][j])
                            p++;
                        j++;
                    }
                    if(p==j-1)
                        cout<<" "<<str_dic[i];
                }
                int diff = in_str.size()-str_dic[i].size();
                if(diff==1||diff==-1){
                    unsigned int m=0,n=0,j=0;
                    while(m<in_str.size()&&n<str_dic[i].size()){
                        if(in_str[m]==str_dic[i][n]){
                            j++;
                            m++,n++;
                        }else{
                            if(diff==1){
                                m++;
                            }
                            if(diff==-1){
                                n++;
                            }
                        }
                    }
                    //cout<<in_str<<"  "<<str_dic[i]<<"j is "<<j<<" m is "<<m<<" n is "<<n<<endl;
                    if(j==(in_str.size()+str_dic[i].size()-1)/2)
                        cout<<" "<<str_dic[i];
                }
            }
            cout<<endl;
        }
    }

    return 0;
}
