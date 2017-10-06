class element{
	private:
		double number;
		char oper;
		int tag;
	public:
		// if tag is 0, it means the element is a number;
		// if tag is 1, it means the element is a oper(including the ( ))

		element(double num = 0.0,char op = ' ', int t=0){
		       number=num;
		       oper = op;
		       tag = t;
		}
		~element() {};
		int status(){	return tag;}
		void setOper(char op){
			oper = op;
			tag = 1;
		}
		char getOper(){ return oper;}

		void setNumber(double num){
			number = num;
			tag = 0;
		}
		double getNum(){	return number;}	
};
