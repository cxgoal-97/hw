#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;


int main(){
	int a = 4;
	int &b = a;
	int arr[] = {b};

	int d [5] = {1,2,3,4,5};
	int e [5] = d;
	return 0;
}
