#include "Addition.h"
#include "ArithmeticExpression.h"
#include "string"
#include <iostream>
#include "Multiplication.h"
using namespace std;

Add::Add(string lOperand, string rOperand) : ArithmeticExpression(lOperand, rOperand) {}   //constructor add

string Add::evaluate(){  // add both parts of the expression
	result = stof(leftOperand) + stof(rightOperand);   //addinf left and right operands and assigning it to the result
	str = result;  //assigning result to the string
    return to_string((long double)(result));  //returning the result that is casted to an long double
}  //end of evaluate function

void Add::print(){ //print function that is printing expression and the result
	cout << stof(leftOperand) << " + " << stof(rightOperand) << " = "<< result << endl;  // printing expression and result
} // end of the print function
