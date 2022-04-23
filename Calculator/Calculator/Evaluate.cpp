#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <assert.h>
#include "Tokenizer.h"

using namespace std;

double evaluate(vector<Token> tokenExp) {

	//vector array of tokens
	//token.getType()
	//token.getStr()

	stack<Token> tokensInOrder;

	stack<Token> operatorStack;
	queue<Token> outputQueue;

	while (!tokenExp.empty()) {
		tokensInOrder.push(tokenExp.back());
		tokenExp.pop_back();
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
			while (operatorStack.top().getType() != Token::Type::lPara && ( operatorStack.top().getPrec() > currentToken.getPrec() || ( operatorStack.top().getPrec() == currentToken.getPrec() && !currentToken.getRightAssociative()) ) ) {
				outputQueue.push(operatorStack.top());
				operatorStack.pop();
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

	return 10;
}