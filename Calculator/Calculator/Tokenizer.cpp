#include "Tokenizer.h"
#include <vector>
include <string>

class Token{ //what forms a token

public:
	enum class Type{
		Unknown,
		Number,
		Operator,
		lPara,
		rPara,
	};
	Token(type t, std::string& s, int prec = -1, bool ra = false) 
		: type{ t }, str{ s }, precedence{ prec }, rightAssociative{ ra }
	{}
	Type type;//This represents how it should be read in evaluation
	std::string str; //This is what the collection of symbols are
	int precedence; //dont know if we need this yet.
	bool rightAssociative; // not sure why we need this one either

	std::ostream& operator<<(std::ostream& os, Token& token) { // allows us to use the << to write a tokem
		os << token.str;
		return os;
	}


}

// The most key tokenization happing is that all - symbols need to be checked if they are a minus or a negitive sign


std::vector<Token> tokenizer(std::string& expression) {
	std::vector<Token> tokens;

	for (std::string::iterator it = expression.begin(); it != expression.end();++it) { // starts at the bgining of the expression
		if (isdigit(*it)) {
			std::string::iterator start = it;
			bool dec = false;//flag for wether or not we have encountered a . yet
			while (isdigit(*it)||*it=='.') {//checks to see if the char pointed to is a digit and 
				if (!dec && *it=='.') {
					dec = true;
				}
				else if (dec && *it == '.') {
					//TODO
				}
				++it; //if the last char is a digit then it will reach the expression.end() postition
			}
			std::string s = string(start, it);//gets substring
			--it;// moves back one in case we are out of bounds
			tokens.push_back(Token{ Token::type::Number, s });//creates new token with the substring and type
		}
		else if () {

		}
	}

	return tokens;
}
