#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(){
	vector<int> num_array;
	int num;
	while(cin>>num)
		num_array.push_back(num);
	for(auto c:num_array)
		cout<<c<<"  ";
	return 0;
}
