#include "BST.h"
#include <iostream>
#include "city.h"
#include "helpTable.h"
using namespace std;
int main()
{
    BST<string,city> CityDataBase;
    helpTable();
    while(1)
    {
        int cmd;
		cin>>cmd;
		switch(cmd){
		case 1:{
			string inputName;
			int inputX,inputY;
			cout<<"please input the name of the city and the position of the city\n"
					"input name: ";
			cin>>inputName;
			cout<<"input x: ";
			cin>>inputX;
			cout<<"input y: ";
			cin>>inputY;
			city City(inputName,inputX,inputY);
			if(CityDataBase.find(inputName)==NULL){
				cout<<"error! the city has already exist.\n"<<endl;
			}else{
				CityDataBase.insert(inputName,City);
			}
			cout<<"Insert Finished.\n";
			break;
		    }
		case 2:{
            string inputName;
            cout<<"Please input the name.";
            cin>>inputName;
            if(CityDataBase.find(inputName)==NULL)
            {
                cout<<"Not founded.\n";
            }
            else
            {
                city result = CityDataBase.find(inputName);
                cout<<"The city is "<<result.getname()<<" the x: "<<result.getx()<<" the y: "<<result.gety()<<'\n';
            }
            else
            {
                cout<<"Input Error.\n";
            };
            cout<<"Search Finished\n";
            break;
            }
        case 3:{
            string inputName;
            cout<<"Please input the name.  ";
            cin>>inputName;
            if(CityDataBase.find(inputName)==NULL)
            {
                cout<<"Not founded.\n";
            }
            else{
                    CityDataBase.remove(inputName);
                    cout<<inputName<<" has been deleted successfully!\n";
                }
            else{
                    cout<<"Input Error.\n";
                };
                cout<<"Delete Finished\n";
                break;
                }
        case 4:{
                    CityDataBase.clear();
                    cout<<"The database has been Reset successfully!\n";
                    break;
                }
        case 5:{
                    double inputx,inputy,distance;
                    cout<<"Please input x of the point: ";
                    cin>>inputx;
                    cout<<"Please input y of the point: ";
                    cin>>inputy;
                    cout<<"Please input the distance: ";
                    cin>>distance;
                    CityDataBase.NeighboringCity(inputx,inputy,distance);
                    break;
                }
        case 6:{
                    cout<<"Search city by initial char\n";
                    char c;
                    cin>>c;
                    CityDataBase.printByChar(c);
                    break;
                }
        case 0:{
                    cout<<"exit!"<<endl;
                    break;
                    break;
                }
        default:
                {
                    cout<<"error input!"<<endl;
                    break;
                }
            }
        }
        cout<<"Finished\n";
    }
    return 0;
}
