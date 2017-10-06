#ifndef HELPTABLE_H_INCLUDED
#define HELPTABLE_H_INCLUDED
#include<iostream>
using namespace std;
void helpTable()
{
    cout<<"～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～"<<endl;
	cout<<"            welcome to city manager"<<endl;
	cout<<"～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～"<<endl;
	cout<<"input the corresponding number of your command: "<<endl;
	cout<<"1:insert a new data\n2:search a city\n3:delete a city\n"
		  "4:reset the database\n5:find the neighboring cities\n"
		  "6:print city by initial character\n0:exit"<<endl;
}
#endif // HELPTABLE_H_INCLUDED
