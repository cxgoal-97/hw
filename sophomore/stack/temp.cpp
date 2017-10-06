#include<iostream>
#include<string>
#include<stdlib.h>


using std::string;
using std::endl;

int isOperator(char c){
	if(c>='0'&&c<='9')
		return 0;
	return 1;
}

int main(){
	char h[1000];
	std::cin>>h;
	char* po=h;
	//std::cin>>h;
	//std::cout<<h<<endl;
	double nu;
	while(*po!='\0'){
		if(isOperator(*po)){
			std::cout<<*po;
			po++;
		}
		else{
			nu = strtod(po,&po);
			std::cout<<nu<<endl;
		}
	}
	
	/*
	 * if(
	nu = strtod(po,&po);
	std::cout<<nu;
	*/

	return 0;
}
