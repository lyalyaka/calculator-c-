#include "Multiplication.h"
#include "ArithmeticExpression.h"
#include "string"
#include <iostream>
#include "Addition.h"
using namespace std;

Multiply::Multiply(string lOperand, string rOperand) : ArithmeticExpression(lOperand, rOperand) { }   //constructor multiply

string Multiply::evaluate(){  // multiply both parts of the expression

	result = stof(leftOperand) * stof(rightOperand);   //multiply left and right operands and assigning it to the result
	str = result;  //assigning result to the string
	return to_string((long double)(result));  //returning the result that is casted to an integer **** to a float // long double
}  //end of evaluate function

void Multiply::print(){ //print function that is printing expression and the result
	cout << stof(leftOperand) << " * " << stof(rightOperand) << " = "<< (float)result << endl;  // printing expression and result
} // end of the print function
