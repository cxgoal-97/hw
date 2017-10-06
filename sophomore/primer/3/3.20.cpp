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

	vector<int> num_array;
	int num;

	while(cin>>num)
		num_array.push_back(num);
	int len = num_array.size();
	for(int i=0;i<=len/2;i++)
		cout<<num_array[i]+num_array[len-1-i]<<"  ";
	return 0;
}
