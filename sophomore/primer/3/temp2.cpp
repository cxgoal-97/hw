#include <iostream>
#include <string>
#include <vector>
/*
using std::string;
using std::cout;
using std::cin;
using std::endl;
*/
using namespace std;

int main(){
	string str("Some string");
	for(auto c : str)
		cout<<c;
	vector<int>it;
	cout<<(it.begin()==it.end())<<endl;	
	auto f = str.begin();
	while(f!=str.end()){
		cout<<*f;
		f++;
	}
	return 0;
}
