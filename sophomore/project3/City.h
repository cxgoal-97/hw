#include <math.h>
#include <string.h>

using std::string;

class City{
	private:
		double x;
		double y;
		string name;
	public:
		City(double in_x=0,double in_y=0,string in_name="NULL"){
			x = in_x;
			y = in_y;
			name = in_name;
		}
		~City(){};
		double getPosX()	{return x;}
		double getPosY()	{return y;}
		string getName()	{return name;}
		double countDistance(City &t){
			double x_ = t.getPosX()-this->getPosX();
			double y_ = t.getPosY()-this->getPosY();
			return sqrt(x_*x_+y_*y_);
		}
		void setPosX(double in_x)	{double x = in_x;}
		void setPosY(double in_y)	{double y = in_y;}
		void setName(string in_name)	{name = in_name;}
};
