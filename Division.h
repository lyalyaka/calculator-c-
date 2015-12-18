#pragma once
#include "ArithmeticExpression.h"

class Divide: public ArithmeticExpression{  //Divide two expression
public: //making functions public so other classes can access it
	Divide(string lOperand, string rOperand);  //constructor
	string evaluate(); //evaluate two expressions
	void print(); // (left `/` right)
}; //end Divide class
