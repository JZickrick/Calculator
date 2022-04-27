#include "Evaluate.h"

using namespace std;

double evaluate(vector<Token> tokenExp) {

	stack<Token> tokensInOrder;

	stack<Token> operatorStack;
	queue<Token> outputQueue;

	tokenExp.pop_back();

	for (int i = tokenExp.size()-1; i >= 0; --i) {
		tokensInOrder.push(tokenExp.at(i));
		//int test = tokenExp.at(i).getPrec();
		//bool test1 = tokenExp.at(i).getRightAssociative();
		//Token::Type test2 = tokenExp.at(i).getType();
		//std::cout << tokenExp.at(i).getString() << std::endl;
	}

	//std::cout << "The Stack has " << tokensInOrder.size() << " tokens in it" << std::endl;

	while (!tokensInOrder.empty()) {
		Token currentToken = tokensInOrder.top();
		tokensInOrder.pop();
		//std::cout << currentToken.getString() << std::endl;
		if (currentToken.getType() == Token::Type::Number) {
			outputQueue.push(currentToken);
		}
		if (currentToken.getType() == Token::Type::Operator) {
			//there is an operator o2 other than the left parenthesis at the top
			//of the operator stack, and (o2 has greater precedence than o1
			//or they have the same precedence and o1 is left - associative)
			if (!operatorStack.empty()) {
				while (!operatorStack.empty() && (operatorStack.top().getType() != Token::Type::lPara && (operatorStack.top().getPrec() > currentToken.getPrec() || (operatorStack.top().getPrec() == currentToken.getPrec() && !currentToken.getRightAssociative())))) {
					outputQueue.push(operatorStack.top());
					operatorStack.pop();
				}
			}
			operatorStack.push(currentToken);
		}
		if (currentToken.getType() == Token::Type::lPara) {
			operatorStack.push(currentToken);
		}
		if (currentToken.getType() == Token::Type::rPara) {
			while (operatorStack.top().getType() != Token::Type::lPara) {
				assert(!operatorStack.empty());
				outputQueue.push(operatorStack.top());
				operatorStack.pop();
			}
			assert(operatorStack.top().getType() == Token::Type::lPara);
			operatorStack.pop();
		}
	}
	while (!operatorStack.empty()) {
		assert(operatorStack.top().getType() != Token::Type::lPara);
		outputQueue.push(operatorStack.top());
		operatorStack.pop();
	}

	/*
	int temp = outputQueue.size();
	for (int i = 0; i < temp; ++i) {
		std::string typeString;
		switch (outputQueue.front().getType()) {
		case Token::Type::EndOfString: typeString = "End Of String"; break;
		case Token::Type::Number: typeString = "Number"; break;
		case Token::Type::Operator: typeString = "Operator"; break;
		case Token::Type::lPara: typeString = "Left Parentheses"; break;
		case Token::Type::rPara: typeString = "Right Parentheses"; break;
		case Token::Type::Unknown: typeString = "Unknown"; break;
		default: typeString = "!!!The Default Case Was Assigned Here!!!"; break;
		}

		std::cout << typeString << " <-> " << outputQueue.front().getString() << std::endl;
		outputQueue.pop();
	}
	*/


	double answer = 0;
	stack<Token> tempStack;
	int outputQueueSize = outputQueue.size();
	for (int i = 0; i < outputQueueSize; ++i) {
		Token currentToken = outputQueue.front();
		Token::Type currentType = outputQueue.front().getType();
		std::string currentString = outputQueue.front().getString();
		outputQueue.pop();

		if (currentType == Token::Type::Number) {
			tempStack.push(currentToken);
		}
		else if (currentType == Token::Type::Operator) {
			if (currentString == "+") {
				double two = stod(tempStack.top().getString());
				tempStack.pop();
				double one = stod(tempStack.top().getString());
				tempStack.pop();

				answer = one + two;
			}
			else if (currentString == "-") {
				double two = stod(tempStack.top().getString());
				tempStack.pop();
				double one = stod(tempStack.top().getString());
				tempStack.pop();

				answer = one - two;
			}
			else if (currentString == "*") {
				double two = stod(tempStack.top().getString());
				tempStack.pop();
				double one = stod(tempStack.top().getString());
				tempStack.pop();

				answer = one * two;
			}
			else if (currentString == "/") {
				double two = stod(tempStack.top().getString());
				tempStack.pop();
				double one = stod(tempStack.top().getString());
				tempStack.pop();

				answer = one / two;
			}
			else if (currentString == "^") {
				double two = stod(tempStack.top().getString());
				tempStack.pop();
				double one = stod(tempStack.top().getString());
				tempStack.pop();

				answer = pow(one, two);
			}
			else {
				//adds invalid symbol
				//math_exp_string = math_exp_string + tokenString;
				std::cout << "The Answer Is Not Correct" << std::endl;
				return -1;
			}

			std::string answerAsString = to_string(answer);
			Token newToken = { Token::Type::Number, answerAsString };
			tempStack.push(newToken);
		}
		else {
			std::cout << "The Answer Is Not Correct" << std::endl;
			return -1;
		}
	}

	Token answerToken = tempStack.top();
	answer = stod(answerToken.getString());

	return answer;


	//return 0;
}