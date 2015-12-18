#pragma once
#include <iostream>
#include <string>
using namespace std;

class Expression{
public:
	virtual string evaluate(); // evaluate expression and return string representation of the result.
	virtual void print(); // prints expression
	virtual void increment(); //increments expression by 1
//	virtual bool checkForErros();
};
