#include "Evaluate.h"

using namespace std;

double evaluate(vector<Token> tokenExp) {

	stack<Token> tokensInOrder;

	stack<Token> operatorStack;
	queue<Token> outputQueue;

	tokenExp.pop_back();	//removes the end of expression character

	for (int i = tokenExp.size()-1; i >= 0; --i) {
		tokensInOrder.push(tokenExp.at(i));
	}


	while (!tokensInOrder.empty()) {
		Token currentToken = tokensInOrder.top();
		tokensInOrder.pop();

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

				if (two == 0) {
					std::cout << "Error: Divide by 0" << std::endl;
					return INFINITY;
				}

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
				std::cout << "Something Really Bad Went Wrong When Evaluating the Expression" << std::endl;
				std::cout << "Somehow an invalid operator got passed validate and into evaluate" << std::endl;
				return -1;
			}

			std::string answerAsString = to_string(answer);
			Token newToken = { Token::Type::Number, answerAsString };
			tempStack.push(newToken);
		}
		else {
			std::cout << "Something Really Bad Went Wrong When Evaluating the Expression" << std::endl;
			std::cout << "Something other than a Number or Operator ended up on the Output Queue in evaluate" << std::endl;
			return -1;
		}
	}

	Token answerToken = tempStack.top();
	answer = stod(answerToken.getString());

	return answer;
}