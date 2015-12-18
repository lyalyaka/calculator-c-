
#include <iostream>
#include "ArithmeticExpression.h"
using namespace std;

int main() { //main
	string str;  //for passing expr to an object
	string input;  //to store input
	while(true){ //infinite loop
		cout << "Please enter an expression (or # to exit): "; //prompt to enter expression
		cin >> input;  //storing expr in input
		if(input[0] != '#'){ //if input wasn't 
			//else if we just need to evaluate an expression
			str.assign(input); //assign input to str
			Expression *expr = new ArithmeticExpression(str);  //initializing object
			if(expr->evaluate()=="Expression is not well formed") cout<<"Expression is not well formed"<<endl;  //evaluating expression
			else expr->print();
			delete expr; expr = nullptr;  //memory management
		} //end if
		else break;  //else break
	}  //end while loop
	getchar();getchar(); //to stop command line from closing the window
	return 0; //return
} // end of main