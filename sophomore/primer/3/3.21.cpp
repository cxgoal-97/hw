#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(){
	vector<string> str_array{"abc","wed","hallo"};
	for(auto p=str_array.begin();p!=str_array.end();p++)
		cout<<*p<<endl;
	return 0;
}
