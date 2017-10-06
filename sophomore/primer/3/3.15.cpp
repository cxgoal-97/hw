#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(){
	vector<string> str_array;
	string str;
	while(cin>>str)
		str_array.push_back(str);
	for(auto c:str_array)
		cout<<c<<"  ";
	return 0;
}
