#include "Tokenizer.h"
#include "Validate.h"
#include "Evaluate.h"
//#include <iostream>

//Function Declaration
void printMenu();


//Main Program
int main() {

	//Testing Tokenizer (Different test strings are below. Uncomment to use)
	std::string testIn = "W#@$$000/45+3.444--5.0*(.4303)";
	//std::string testIn = "5+6-8";
	//std::string testIn = "5+6-8(5--5)";
	//std::string testIn = "5--5";
	
	std::vector<Token> round1 = tokenizer(testIn);

	std::cout << "TOKENIZER OUTPUT" << std::endl;
	for (int i = 0; i < round1.size(); ++i) {
		Token::Type dummyType = round1.at(i).getType();
		std::string typeString = "";

		switch (dummyType) {
		case Token::Type::EndOfString: typeString = "End Of String"; break;
		case Token::Type::Number: typeString = "Number"; break;
		case Token::Type::Operator: typeString = "Operator"; break;
		case Token::Type::lPara: typeString = "Left Parentheses"; break;
		case Token::Type::rPara: typeString = "Right Parentheses"; break;
		case Token::Type::Unknown: typeString = "Unknown"; break;
		default: typeString = "!!!The Default Case Was Assigned Here!!!"; break;
		}

		std::cout << typeString << " <-> " << round1.at(i).getString() << std::endl;
	}

	std::cout << "\n\nTEST OF VALIDATE" << std::endl;
	bool isValid = false;
	isValid = validate(round1);
	if (isValid) {
		std::cout << "VALID" << std::endl;
	}
	else {
		std::cout << "NOT VALID" << std::endl;
	}

	//
	//MAIN PROGRAM
	//

	/*
	//Variable Declarations
	std::string userInput = "";			//String for user input
	bool isValidInput = false;		//Holds a value for if the user input is valid

	//print menu
	printMenu();

	while (userInput != "Q" || userInput != "q") {
		do {
			std::cout << "-> ";
			getline(std::cin, userInput);

			if (userInput == "m" || userInput == "M") { printMenu(); }
			if (userInput == "c" || userInput == "C") { system("cls"); }
			if (userInput == "q" || userInput == "Q") { return 0; }
		} while (userInput == "M" || userInput == "m" || userInput == "c" || userInput == "C");

		std::vector<Token> userInputTokens = tokenizer(userInput);

		isValidInput = validate(userInputTokens);

		if (isValidInput) {
			std::cout << "Valid" << std::endl;
			int answer = 0;
			//answer = evaluate(userInputTokens);
			std::cout << answer << std::endl;
		}
		else {
			std::cout << "Invalid" << std::endl;
		}

		std::cout << std::endl;
	};
	*/

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