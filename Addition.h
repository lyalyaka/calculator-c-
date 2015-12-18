#pragma once
#include "ArithmeticExpression.h"

class Add: public ArithmeticExpression{   //Add two expression
public: //making functions public so other classes can access it
	Add(string lOperand, string rOperand);   //constructor
	string evaluate(); //evaluate two expressions
	void print(); // (left `+` right)
}; // end Add class
