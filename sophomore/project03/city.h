#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED
class city
{
private:
	string name;
	int x,y;
public:
	city(string cname="none",int cx=0,int cy=0){
        name=cname;
        x=cx;
        y=cy;
	};
	string getname(){return name;};
	int getx(){return x;};
	int gety(){return y;};
};


#endif // CITY_H_INCLUDED
