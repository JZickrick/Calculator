#include <iostream>
#include <string>
#include "Validate.h"

using namespace std;

int main() {

	string userInput;

	cout << "Enter an arithmetic expression: ";
	getline(cin, userInput);

	cout << "result is: " << validate(userInput);

	return 0;
}