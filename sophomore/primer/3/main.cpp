#include<iostream>
#include<string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(){
	string s1 = "123";
	string s2 = "234";
	cout<<s1[3]<<endl;
	cout<<s2[3]<<endl;
	s1 = s1 + s2 ;
	cout<<s1[6]<<endl;
	cout<<s1<<endl;
	//while (getline(cin,s1))
	while(cin>>s1)
		if(!s1.empty())
		cout<<s1<<endl;
	int len = s1.size();
	return 0;
}
