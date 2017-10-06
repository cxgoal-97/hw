#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;


int main(){
	string s1;
	cin>>s1;
	if(s1.size()<-5)
		cout<<"Delete\n";
	string s2;
	cin>>s2;
	s1 = (s2+"hel")+"je";
	cout<<s1<<endl;
	return 0;
}
