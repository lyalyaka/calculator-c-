#pragma once
#include "ArithmeticExpression.h"

class Subtract: public ArithmeticExpression{  //Subtract two expression
public: //making functions public so other classes can access it
	Subtract(string lOperand, string rOperand);  //constructor
	string evaluate(); //evaluate two expressions
	void print(); // (left `-` right)
}; //end substruct class
