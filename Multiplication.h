#pragma once
#include "ArithmeticExpression.h"

class Multiply: public ArithmeticExpression{  //Multiply two expressions
public:  //making functions public so other classes can access it
	Multiply(string lOperand, string rOperand); //constructor
	string evaluate();  //evaluate two expressions
	void print(); // (left `*` right)
};  //end Multiply class
