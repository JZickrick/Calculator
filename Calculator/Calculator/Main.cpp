#include <iostream>
#include <string>
#include "Validate.h"
#include "Evaluate.h"

using namespace std;

int main() {

	string userInput;

	cout << "Enter an arithmetic expression: ";
	getline(cin, userInput);

	while (!validate(userIntput) || userInput == "Q" || userInput =="q" ) {
		cout << "Please enter the arithmetic expression again with the error, or enter Q/q to quit";
		getline(cin, userInput);
	}
	if (userInput == "q" || userInput == "Q") {
		cout << "Thanks for running the program!";
		return 0;
	}
	//this point user input has been validated
	
	cout << "result is: " << validate(userInput);
	

	return 1;
}