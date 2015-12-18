#include "ArithmeticExpression.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"
#include <algorithm>
#include <stack>
#include <list>
#include <typeinfo>
#include <string> //added
#include <iostream>
#include <algorithm>
using namespace std;

ArithmeticExpression::ArithmeticExpression(string s){ // constructor for arithmetic expression that takes a string
	left  = right = nullptr; // initialize the left and right pointers to null
	result = 0.00; // initialize result to 0.00
//*****apparently we're supposed to remove the whitespace checker
	auto iter(remove_if(s.begin(), s.end(), isspace));
	s.erase(iter,s.end());
	str.assign(s);
	evalResult = "Expression is not well formed";
}

ArithmeticExpression::ArithmeticExpression(string lOperand, string rOperand){ // another arithmeticexpression constructor that takes leftOperand and rightOperand strings
	left = right = nullptr; // left and right pointers are initalized to null
	leftOperand = lOperand; // leftOperand is initialized to lOperand
	rightOperand = rOperand; // rightOperand is inialized to lOperand
	result = 0.00; // result is initialized to zero
	evalResult = "Expression is not well formed";
}


ArithmeticExpression::ArithmeticExpression(const ArithmeticExpression &obj){  //copy constructor
	left  =  right = nullptr;  // initialize the left and right pointers to null
	result = 0.00; // initialize result to 0.00
	this->str.assign(obj.str);  //copy sting to a local string
	evalResult = "Expression is not well formed";
}


ArithmeticExpression::~ArithmeticExpression(){ // destructor for arithmetic expression
	delete left; // delete the memory allocated to left pointer
	delete right; // delete the memory allocated to right pointer
	left = right = nullptr; // set both pointers to null
}


bool ArithmeticExpression::isSymbol(char c){ // checks if the character is a +, -, /, or *
	return (c==42 || c==43 || c==45 || c==47) ? true : false ; // if c is * or + or - or / return true
}


bool ArithmeticExpression::checkForErros(){ // this checks if the expression is legitimate
	stack<char> brackets; //declaring stack for brackets eval
	list<char> expr;  //declaring list for expression eval

	for (int i=0; i<str.length(); i++) {  //for loop declaration to loop throught the entire expression
		if(str[i] == '('){  //test for open bracket
			brackets.push(str[i]);  //add to the stack
			if(str[i+1]=='-') i++; //check if number in the brackets is negative, if so, skip the '-' sign
		} //end if
		else if (str[i] == ')') { //check for closing brackets
			if (brackets.empty() || brackets.top() != '(') return false; //if stack is empty or top element of the stack is not the open bracket then expr is invalid, return false
			brackets.pop();  //pop the top element of the stack, which is an opening bracket
		} //end of else if

		else{  //else
			if(expr.empty() && str[i]=='-' && i==0) ; //negative digit in front of expression test
			else if(str.length()==1 || expr.empty()) expr.push_back(str[i]);  //if str is empty or with 1 digit, push to the end of the list
			else if( isdigit(expr.back()) && isdigit(str[i]) ) ; //do nothing, skip -> for multiple digit ints
			else expr.push_back(str[i]) ;  //else push to the back of the stack
		}  //end else
	}  //end for loop
	while ( !expr.empty() && brackets.empty()){  //test expr
		if(expr.size() == 1) return (isdigit(expr.front()) || isSymbol(expr.front())  ) ? true : false ;  //if expr is only one digit return true, else false

		else if( isdigit(expr.front()) && isdigit(expr.back()) ){ //if digit in at the fron and back of the list then pop both
			expr.pop_front();  //pop front
			expr.pop_back();  //pop back
			if( expr.size() > 1 && ( isSymbol(expr.back()) && isSymbol(expr.front()) ) ){ // if symbols are at the front and back of the expression then pop both
				expr.pop_front();  //pop front
				expr.pop_back();  //pop back
			}  //end if
		}  //end else if
		else return false;  //return false if expr is invalid
	} //end while loop
	return false;  //return false if expr is invalid
}  //end checkForErrors


string ArithmeticExpression::evaluate(){ // parses and evaluates the arithmetic expression
	ArithmeticExpression *ptrOperand = nullptr;

	if( checkForErros() ){ // if checkForErros returns false, the code in this block is not executed and the function returns expression is not well-formed
		stack<char> brackets; // declare a char stack called brackets
		string leftStr; // declare string leftStr
		string rightStr; // declare string rightStr
		for (int j = 0; j < str.length(); j++) { // search over the entire expression
			if(str[j] == '('&&str[j+1]=='('){str = Parentheses(str, '(', j); j++;} // if there are two left brackets in a row, run a function that merges all sequential brackets into one
			if(str[j] == ')'&&str[j+1]==')'){str = Parentheses(str, ')', j); j++;} // if there are two right brackets in a row, run a function that merges all sequential brackets into one
		}
		for(int i=0; i<str.length(); i++) // loops over the entire expression
		{
			if(is_number(str)){evalResult = str;} // if the expression is just a number, the number is assigned evalResult, so the number will be returned
			if((str[0]=='(') && is_number(str.substr(1,str.length()-1))) {str = str.substr(1,str.length()-1);} // remove extra left bracket
			if((str[str.length()-1] == ')')&& is_number(str.substr(0,str.length()-2))){str = str.substr(0,str.length()-2);} // remove extra right bracket
			if ((str[0]=='(')&&(str[1]=='-')&&(str[str.length()-1]==')')&&(is_number(str.substr(2,str.length()-2)))) {str = "0-"+str.substr(2,str.length()-2);} // if it's a negative number, covert it to 0-the number
			if ((str[0]=='(')&&str[str.length()-1]==')'&&is_number(str.substr(1,str.length()-2))) {str = str.substr(1,str.length()-2);} // if there's a number enclosed in brackets, remove the brackets
			if(str[i] == '('){ // if the character is a left bracket
				int c = i; string temp; // note the current index and initialize string temp
				brackets.push(str[i]); // push to the brackets stack
				while (!brackets.empty()){ // while the bracket stack is not empty
				temp.push_back(str[i]); // add element to temp
				i++; // increment i by 1
				if (str[i] == ')') brackets.pop();} // if the element is a right bracket, remove a bracket from the bracket stack
				temp.erase(temp.begin()); // remove brackets from the string
				if (!(str.length()== temp.length())&&(((str.length()-temp.length())%2) == 0)) { // if the difference between the length of the string and the length of temp is divisible by 2
					if (c == 0){ // if the left bracket was at the beginning of the string
					if (i == (str.length()-1)) {str = temp; i=1;} // if the end of the string was reached, assign temp to str
					else {leftStr = temp; i++;} // otherwise assign temp to left and increment i
				}
				else {rightStr = temp;} // otherwise assign temp to right Str
				}
			}



			if (isSymbol(str[i])) // if the element of the string is a symbol
			{
				if (containsAS(str)) {
						if(str[i] == '+' || str[i] == '-'){  //operator
							if (rightStr.empty()) {rightStr.assign(str,i+1,str.length()-1);} // if rightStr hasn't been assigned yet, assign it to everything before the symbol
							if (leftStr.empty()) {leftStr.assign(str,0,i);} // if leftStr hasn't been assigned yet, assign it to everything before the symbol
							if((rightStr[0]=='(') && is_number(rightStr.substr(1,rightStr.length()-1))) {rightStr = rightStr.substr(1,rightStr.length()-1);} // remove extra left bracket at the beginning of the right expression
							if((rightStr[rightStr.length()-1] == ')')&& is_number(rightStr.substr(0,rightStr.length()-2))){rightStr = rightStr.substr(0,rightStr.length()-2);} // remove extra right brackfrom from the beginning of the right expression
							if((leftStr[0]=='(') && is_number(leftStr.substr(1,leftStr.length()-1))) {leftStr = leftStr.substr(1,leftStr.length()-1);} // remove extra left bracket at the beginning of the left expression
							if((leftStr[leftStr.length()-1] == ')')&& is_number(leftStr.substr(0,leftStr.length()-2))){leftStr = leftStr.substr(0,leftStr.length()-2);} // remove extra right bracket at the beginning of the left expression
							if ((leftStr[0]=='(')&&leftStr[leftStr.length()-1]==')'&&is_number(leftStr.substr(1,leftStr.length()-2))) {leftStr = leftStr.substr(1,leftStr.length()-2);} // if the left string is a number enclosed in brackets, remove the brackets
							if ((rightStr[0]=='(')&&rightStr[rightStr.length()-1]==')'&&is_number(rightStr.substr(1,rightStr.length()-2))) {rightStr = rightStr.substr(1,rightStr.length()-2);} // if the right string is a number enclosed in brackets, remove the brackets
							left = new ArithmeticExpression(leftStr); // create a new arithmetic expression object with the left string
							right = new ArithmeticExpression(rightStr); // create a new arithmetic expression object with the right string
							if (str[i]=='+') {i++; ptrOperand = new Add(left->evaluate(), right->evaluate());} // if the symbol is +, create an Add object and evaluate the left and right operands
							else if (str[i]=='-') { ptrOperand = new Subtract(left->evaluate(), right->evaluate()); } // if the symbol is -, create a Subtract object and evaluate the left and right operands
						}
				}
				else {
					const int strlength = str.length();
					if (str.length() == strlength) {str = stringrev(str);}
					if(str[i] == '*' || str[i] == '/'){  // if the operator is either * or /
						if (rightStr.empty()) {rightStr.assign(str,i+1,str.length()-1);} // if rightStr hasn't been assigned, assign to it everything to the right of the symbol
						if (leftStr.empty()) {leftStr.assign(str,0,i);} // if leftStr hasn't been assigned, assign to it everything to the right of the symbol
						if((rightStr[0]=='(') && is_number(rightStr.substr(1,rightStr.length()-1))) {rightStr = rightStr.substr(1,rightStr.length()-1);} // remove extra left bracket at the beginning of the right expression
						if((rightStr[rightStr.length()-1] == ')')&& is_number(rightStr.substr(0,rightStr.length()-2))){rightStr = rightStr.substr(0,rightStr.length()-2);} // remove extra right brackfrom from the beginning of the right expression
						if((leftStr[0]=='(') && is_number(leftStr.substr(1,leftStr.length()-1))) {leftStr = leftStr.substr(1,leftStr.length()-1);} // remove extra left bracket at the beginning of the left expression
						if((leftStr[leftStr.length()-1] == ')')&& is_number(leftStr.substr(0,leftStr.length()-2))){leftStr = leftStr.substr(0,leftStr.length()-2);} // remove extra right bracket at the beginning of the left expression
						if ((leftStr[0]=='(')&&leftStr[leftStr.length()-1]==')'&&is_number(leftStr.substr(1,leftStr.length()-2))) {leftStr = leftStr.substr(1,leftStr.length()-2);} // if the left string is a number enclosed in brackets, remove the brackets
						if ((rightStr[0]=='(')&&rightStr[rightStr.length()-1]==')'&&is_number(rightStr.substr(1,rightStr.length()-2))) {rightStr = rightStr.substr(1,rightStr.length()-2);} // if the right string is a number enclosed in brackets, remove the brackets
						left = new ArithmeticExpression(leftStr); // create a new arithmetic expression object with the left string
						right = new ArithmeticExpression(rightStr); // create a new arithmetic expression object with the right string
						if (str[i]=='*') {i++;ptrOperand = new Multiply(left->evaluate(), right->evaluate()); }// if the symbol is *, create an Add object and evaluate the left and right operands
						else if (str[i]=='/') {ptrOperand = new Divide(left->evaluate(), right->evaluate());} // if the symbol is /, create an Add object and evaluate the left and right operands
						i++;
					}
				}
			}
			if (!(ptrOperand==nullptr)) {
			evalResult = ptrOperand->evaluate(); // evaluate the expression pointed to by ptrOperand
			delete ptrOperand; // delete the memory allocated to the pointer
			ptrOperand = nullptr; // set the pointer to null
			break; // break out of the for loop
			}

		}
		this->result = convert(evalResult); // convert the result to a numerical format
	}
	return evalResult; // return evalResult, which is a number if it's a legitimate expression, or an error message if it's not a legitimate expression
}


void ArithmeticExpression::print(){ // print the arithmetic expression
//	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
//	cout.precision(2);
	cout << str << " = " << fixed << evaluate() << endl;
}


float ArithmeticExpression::convert(string s){ // convert a string to a float
	return stof(s); // return the string converted to a float
}

bool ArithmeticExpression::is_number(const std::string& s) // check if a string is a number
{
	// check if the string is empty, and check each character in the string to see if it is a number, if it's not empty and if all characters are digits return true
	 bool number = true; // initialize number to true
	    if (str.empty()) {number = false;} // change number to false if the string is empty
	    for (int i = 0; i < str.length(); i++) { // loop over each character in the string
	        if(!isdigit(str[i])) {number = false;} // if one of the characters is not a number, set number to false
	    }
	 return number; // return number, which will be true if the string is
}

string ArithmeticExpression::stringrev(const std::string& s) // check if a string is a number
{
	string temp = "";
	// check if the string is empty, and check each character in the string to see if it is a number, if it's not empty and if all characters are digits return true
	    for (int i = 0; i < str.length(); i++) { // loop over each character in the string
	        temp = s[i] + temp; // if one of the characters is not a number, set number to false
	    }
	 return temp; // return number, which will be true if the string is
}

bool ArithmeticExpression::containsAS(string str) {
	bool oper = false;
	for (int i = 0; i < str.length(); i++) { // loop over each character in the string
		if(str[i] == '+' || str[i] == '-') {oper = true;} // if one of the characters is not a number, set number to false
	}
	return oper;
}

bool ArithmeticExpression::containsDiv(string str) {
	bool oper = false;
	for (int i = 0; i < str.length(); i++) { // loop over each character in the string
		if(str[i] == '/') {oper = true;} // if one of the characters is not a number, set number to false
	}
	return oper;
}

string ArithmeticExpression::Parentheses(string str, char a, int k) { // this function contracts sequential left or right brackets, so '((' would be converted to '('
	int count = 0; // initialize a variable to count brackets
	int i; // intialize a loop variable
	for (i=k+1; i<str.length(); i++) { // start from the location in the string where the bracket was found
		while (str[i] == a) {count++; i++;} // if the element of the string is a left or right bracket, increment count and increment i
		break; // break out of the loop once an element that is not a bracket is accessed
	}
	if (a=='(') { // if a is a left bracket
		if (k==0) {str = str.substr(k+count, str.length());} // if the bracket is at the beginning of the expression, create a substring going from the last bracket to the end of the string
		else {str = str.substr(0,k) + str.substr(k+count,str.length());} // otherwise create a substring that excludes the extra brackets
	}
	if (a==')') { // if a is a right bracket
		if (i == str.length()-1) {str = str.substr(0,k+1);} // if the bracket is at the end of the expression, create a substring that goes from the beginning of the string to the first right bracket
		else {str = str.substr(0,k) + str.substr(k+count,str.length());} // otherwise create a substring that excludes the extra brackets
	}
	return str; // return the string with extra brackets removed
}

void ArithmeticExpression::increment(){ // increment every digit in the expression
	for(int i=0; i<str.length(); i++) { // loop over the entire expression
		if(isdigit(str[i])) str[i]++; // if the element is a digit, increment it by 1
	}
}
