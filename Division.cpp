#include "Division.h"
#include "ArithmeticExpression.h"
#include "string"
#include <iostream>
using namespace std;

Divide::Divide(string lOperand, string rOperand) : ArithmeticExpression(lOperand, rOperand) {  } //constructor Divide

string Divide::evaluate(){   // Divide right part of the expression from the left part
	result = stof(rightOperand) /stof(leftOperand) ;
	//  result = stof(leftOperand) / stof(rightOperand);  //Divide right operand from the left operand and assigning it to the result ***** was subtraction, changed to division
	str = result;   //assigning result to the string
	return to_string((long double)(result));    //returning the result that is casted to an integer // long double
}   //end of evaluate function

void Divide::print(){   //print function that is printing expression and the result
	cout << stof(leftOperand) << " / " << stof(rightOperand) << " = "<< (float)result << endl;  // printing expression and result
}  // end of the print function
