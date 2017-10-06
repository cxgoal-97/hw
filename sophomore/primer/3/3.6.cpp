#include <iostream>
#include <string>
#include <cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;


int main(){
	string s1;
	cin>>s1;
	for(char &c:s1){
		if(isalnum(c))
			c='x';
	}

	cout<<s1<<endl;
	return 0;
}
