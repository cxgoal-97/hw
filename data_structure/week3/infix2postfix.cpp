//
#include <iostream>
#include <cstdio>
#include <string>
#include <stack>

using namespace std;

// 将中缀表达式转换为后缀表达式
string infix2postfix(string i_string);

int main(){
    int k = 0;
    cin>>k;
    getchar();
    for(int j=0; j<k; j++){
    	string i_string;
        getline(cin, i_string);
        string t_string;
        getline(cin,t_string);
        string result = infix2postfix(i_string);
        string result_t = infix2postfix(t_string);
        cout<<result<<endl;
        cout<<result_t<<endl;
    }
	return 1;
}


string infix2postfix(string i_string){
    string result;
    stack<char> stack_a;
	for(unsigned int i=0; i<i_string.length(); i++){
        char t = i_string[i];
        // 排除空格和tab
        if (t=='\t'||t==' '||t=='\n')
            continue;
        // 如果为 左括号
        else if(t=='(')
            stack_a.push(t);
        // 如果为 高级别操作数
        else if(t=='/'||t=='*'){
            while(!stack_a.empty()&&(stack_a.top()=='/'||stack_a.top()=='*')){
                result = result+stack_a.top();
                stack_a.pop();
            }
            stack_a.push(t);
        }
        // 如果为 低级别操作数，
        // 若栈中有高级别操作数，则显示并弹出
        else if(t=='+'||t=='-'){
            while(!stack_a.empty()&&
                    (stack_a.top()!='(')){
                result = result+stack_a.top();
                stack_a.pop();
            }
            stack_a.push(t);
        }

        // 如果为 右括号
        else if(t==')'){
            while(stack_a.top()!='('){
                //cout<<stack_a.top();
                result = result+stack_a.top();
                stack_a.pop();
            }
            stack_a.pop();
        }else
            result = result+t;
	}
    while(!stack_a.empty()){
        result = result+stack_a.top();
        stack_a.pop();
    }
    return result;
}

