#include <iostream>
#include <string>

/*
using std::string;
using std::cout;
using std::cin;
using std::endl;
*/
using namespace std;
int main(){
	string s1,s2;
	
	cin>>s1;
	cin>>s2;

	if(s1==s2)
		cout<<"两者相等"<<endl;
	else if(s1>s2)
		cout<<s1<<endl;
	else
		cout<<s2<<endl;
	
	cin>>s1;
	cin>>s2;
	
	string temp("1323");
	auto len = 42l;
	int lenS1 = s1.size();
	int lenS2 = s2.size();
	if(lenS1==lenS2)
		cout<<"两者字符串相等"<<endl;
	else if(lenS1>lenS2)
		cout<<s1<<endl;
	else
		cout<<s2<<endl;

	return 0;
}
