#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;


int main(){
	string s1;
	//读入一整行
	//while(getline(cin,s1))
	//	cout<<s1<<endl;
	
	//读入一个词语
	while(cin>>s1)
		cout<<s1<<endl;

	return 0;
}
