/*

#include "Tokenizer.h"
#include "Validate.h"
#include "Evaluate.h"



//Main Program
int main() {

	//Testing Tokenizer (Different test strings are below. Uncomment to use)
	//std::string testIn = "W#@$$000/45+3.444--5.0*(.4303)";
	//std::string testIn = "5+6-8";
	//std::string testIn = "5+6-8(5--5)";
	std::string testIn = "5--5";

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

		int answer = 0;
		answer = evaluate(round1);
		std::cout << answer << std::endl;
	}
	else {
		std::cout << "NOT VALID" << std::endl;
	}
	

	return 0;
}

*/