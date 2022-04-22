#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

void printMenu();

int main() {

	string userInput = "";

	printMenu();

	while (userInput != "Q" || userInput != "q") {
		do {
			cout << "-> ";
			getline(cin, userInput);
			if (userInput == "m" || userInput == "M") {
				printMenu();
			}
			if (userInput == "c" || userInput == "C") {
				system("cls");
			}
			if (userInput == "q" || userInput == "Q") {
				return 0;
			}
		} while (userInput == "M" || userInput == "m" || userInput == "c" || userInput == "C");

		bool isValid = false;
		isValid = validate(userInput);

		if (isValid) {
			cout << "Valid" << endl;
		}
		else {
			cout << "Invalid" << endl;
		}

		cout << endl;
	};
	

	return 0;
}

void printMenu() {
	cout << "Welcome to the Awesome Calculator Application for MSCS-271!" << endl;
	cout << "Valid arithmatic expressions include: + - * / ^ ( )" << endl;
	cout << "You may also perform implicit multiplication as well as use a negative (-) sign for negative numbers" << endl;
	cout << "This means 5--5 is a valid expression as well as 5(5+5)" << endl;
	cout << "At any time you can type any of the following commands:" << endl;
	cout << "\t(m) - print menu" << endl;
	cout << "\t(c) - clear screen" << endl;
	cout << "\t(q) - quit" << endl;
	cout << endl;
}