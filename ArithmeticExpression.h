#pragma once
#include "Expression.h"

class ArithmeticExpression : public Expression{
	Expression *left;
	Expression *right;
public: //making functions public so other classes can access it
	float result;   // ***** changed this to a float, otherwise integer division happens
	string evalResult; // evalResult is initialized to Expression is not well formed
	string str;
	string leftOperand;
	string rightOperand;
	ArithmeticExpression(string s);   //constructor
	ArithmeticExpression(string lOperand, string rOperand);   //constructor
	ArithmeticExpression(const ArithmeticExpression &obj);
	~ArithmeticExpression();  //destructor, check to make sure that its implementation releases all dynamically allocated memory
	bool isSymbol(char c);
	bool checkForErros();
	string evaluate(); //evaluate left expression and right expression
	void print(); // prints expression
	float convert(string s); // Converts a string (as would be returned by evaluate) to a float
	bool ArithmeticExpression::is_number(const std::string& s); // checks if a string is a number
	string ArithmeticExpression::stringrev(const std::string& s);
	bool ArithmeticExpression::containsAS(string str); // checks if there is a + or - operator
	bool ArithmeticExpression::containsDiv(string str);
	string Parentheses(string str, char a, int k); // contracts sequential parentheses
	void increment(); //increments expression by 1

};  //end ArithmeticExpression class
