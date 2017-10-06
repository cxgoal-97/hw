#include "BST.h"
#include "City.h"

using std::cin;
using std::endl;

int main(){
	BST<string,City> T;
	while(1)
    	{
		int cmd;
		cin>>cmd;
		switch(cmd){
		case 1:{
		    string inputName;
		    double inputX,inputY;
		    cout<<"please input the name of the city and the position of the city\n"
		            "input name: ";
		    cin>>inputName;
		    cout<<"input x: ";
		    cin>>inputX;
		    cout<<"input y: ";
		    cin>>inputY;
		    City t(inputX,inputY,inputName);
		    T.insert(inputName,t);
		    cout<<"Insert Finished.\n";
		    break;
		    }
		case 2:{
		    cout<<"which city would you like to search the city. \n";
		    cout<<"Please input name.\n";
		    string inputName;
		    cout<<"Please input the name.";
		    cin>>inputName;
		    City *t = T.find(inputName);
		    if(t==NULL)
			    cout<<"The Node is not exit.\n";
		    else
			    cout<<t->getName()<<" x:"<<t->getPosX()<<" y:"<<t->getPosY()<<"\n";

		    break;
		       }
		        case 3:{
		                cout<<"which one would you like to delete .\n";
		                cout<<"Please input the name.\n";
				string inputName;
		    		cin>>inputName;
				T.remove(inputName);	
		                break;
		            }
		    case 4:{
				cout<<"Search city be first char\n";
				char c;
				cin>>c;
				T.printByChar(c);
		                break;
		            }
		    case 5:{
		    		double x,y;
		                double distance;
		                cout<<"Please input the x: ";
		                cin>>x;
		                cout<<"Please input the y: ";
		                cin>>y;
		                cout<<"Please input the distance: ";
		                cin>>distance;
				T.printByDis(x,y,distance);
		                break;
		            }
		    case 6:{
		        cout<<"exit!"<<endl;
		        break;
		        }
		    default:
		        cout<<"Error input\n";
		    }
	}
	return 0;
}


