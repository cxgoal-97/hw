#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(){
	/*
	for(auto c:str_array)
		cout<<c<<" ";
	*/

	vector<int> num(10,42);
	cout<<num.size()<<endl;
	return 0;
}
