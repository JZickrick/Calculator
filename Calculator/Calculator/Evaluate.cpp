#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <assert.h>

using namespace std;

enum myType {
	UNKNOWN = 0, NUMBER = 1, OPERATOR = 2, lPara = 3, rPara = 4
};

class token {
public:
	int getType() {
		return 1;
		//for reference of what getType will return
		//Unknown,		//0
		//Number,		//1
		//Operator,		//2
		//lPara,		//3
		//rPara,		//4
	}
	string getString() {
		return "Test String";
	}
	int getPrecedence() {
		return 1;
	}
	bool getRightAssociative() {
		return true;
	}

private:

};

double evaluate(vector<token> tokenExp) {

	//vector array of tokens
	//token.getType()
	//token.getStr()

	stack<token> tokensInOrder;

	stack<token> operatorStack;
	queue<token> outputQueue;

	while (!tokenExp.empty()) {
		token temp;
		temp = tokenExp.back();
		tokenExp.pop_back();
		tokensInOrder.push(temp);
	}

	while (!tokensInOrder.empty()) {
		token currentToken = tokensInOrder.top();
		tokensInOrder.pop();
		if (currentToken.getType() == NUMBER) {
			outputQueue.push(currentToken);
		}
		if (currentToken.getType() == OPERATOR) {
			//there is an operator o2 other than the left parenthesis at the top
			//of the operator stack, and (o2 has greater precedence than o1
			//or they have the same precedence and o1 is left - associative)
			while (operatorStack.top().getType() != lPara && ( operatorStack.top().getPrecedence() > currentToken.getPrecedence() || ( operatorStack.top().getPrecedence() == currentToken.getPrecedence() && !currentToken.getRightAssociative()) ) ) {
				outputQueue.push(operatorStack.top());
				operatorStack.pop();
			}
			operatorStack.push(currentToken);
		}
		if (currentToken.getType() == lPara) {
			operatorStack.push(currentToken);
		}
		if (currentToken.getType() == rPara) {
			while (operatorStack.top().getType() != lPara) {
				assert(!operatorStack.empty());
				outputQueue.push(operatorStack.top());
				operatorStack.pop();
			}
			assert(operatorStack.top().getType() == lPara);
			operatorStack.pop();
		}
	}
	while (!operatorStack.empty()) {
		assert(operatorStack.top().getType() != lPara);
		outputQueue.push(operatorStack.top());
		operatorStack.pop();
	}


}