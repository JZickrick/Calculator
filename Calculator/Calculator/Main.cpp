#include "Tokenizer.h"
#include "Validate.h"
#include "Evaluate.h"

//Function Declaration
void printMenu();


//Main Program
int main() {
	//
	//MAIN PROGRAM
	//

	
	//Variable Declarations
	std::string userInput = "";			//String for user input
	bool isValidInput = false;		//Holds a value for if the user input is valid

	//print menu
	printMenu();

	while (userInput != "Q" || userInput != "q") {
		do {
			std::cout << "-> ";
			getline(std::cin, userInput);

			//removes white space from user input
			std::regex space_pattern("(\\s)");
			userInput = regex_replace(userInput, space_pattern, "");

			if (userInput == "m" || userInput == "M") { printMenu(); }
			if (userInput == "c" || userInput == "C") { system("cls"); }
			if (userInput == "q" || userInput == "Q") { return 0; }
		} while (userInput == "M" || userInput == "m" || userInput == "c" || userInput == "C");

		std::vector<Token> userInputTokens = tokenizer(userInput);


		isValidInput = validate(userInputTokens);

		if (isValidInput) {
			//std::cout << "Valid" << std::endl;
			double answer = 0;
			answer = evaluate(userInputTokens);
			std::cout << answer << std::endl;
		}
		else {
			std::cout << "Invalid" << std::endl;
		}

		std::cout << std::endl;
	};

	return 0;
}

//Menu Print Function
void printMenu() {
	std::cout << "Welcome to the Awesome Calculator Application for MSCS-271!" << std::endl;
	std::cout << "Valid arithmatic expressions include: + - * / ^ ( )" << std::endl;
	std::cout << "You may also perform implicit multiplication as well as use a negative (-) sign for negative numbers" << std::endl;
	std::cout << "This means 5--5 is a valid expression as well as 5(5+5)" << std::endl;
	std::cout << "At any time you can type any of the following commands:" << std::endl;
	std::cout << "\t(m) - print menu" << std::endl;
	std::cout << "\t(c) - clear screen" << std::endl;
	std::cout << "\t(q) - quit" << std::endl;
	std::cout << std::endl;
}