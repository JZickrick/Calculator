#include "Tokenizer.h"


std::vector<Token> tokenizer(std::string& expression) {
	std::vector<Token> tokens;
	expression.append("$");
	for (std::string::iterator it = expression.begin(); it != expression.end(); ++it) { // starts at the bgining of the expression
		if (isdigit(*it)) {
			std::string::iterator start = it;

			bool dec = false;//flag for wether or not we have encountered a . yet
			while ((isdigit(*it) || ((*it) == '.' && !dec)) && (*it)!='$') {//checks to see if the char pointed to is a digit or  a . that has not come after another . or if we have reached end of text character
				if (!dec && *it == '.') { // if it is a period and we havent see one yet then we enter it
					dec = true;
				}
				++it; //if the last char is a digit then it will reach the $ char
			}
			std::string toAdd = std::string(start, it);//gets substring
			--it;// moves back one in case we are out of bounds
			tokens.push_back(Token{ Token::Type::Number, toAdd });//creates new token with the substring and type
		}
		else if ((*it) == '.') {
			std::string::iterator start = it;
			++it; //moves past decimal point
			while (isdigit(*it) && (*it)!='$') {
				++it;
			}
			if ((&(*(++start))) == (&(*it))) { // this checks to see if adressess of the objects the being pointed to are the same
				//create an unknown token
				std::string str = ".";
				tokens.push_back(Token{ Token::Type::Unknown, str });
			}
			else { //create a number token
				--start;
				std::string str = std::string(start, it);
				tokens.push_back(Token{ Token::Type::Number, str });
			}
			--it;
		}
		else { //This handles anything that might not be a number. **THIS DOES NOT MOVE NEGITIVES INTO NUMBERS, ALL - SIGNS ARE READ IN AS OPERATORS**
			Token::Type t = Token::Type::Unknown;
			int prec = -1;
			bool ra = false;
			switch (*it) {
			default:
				break;
			case ')':
				t = Token::Type::rPara;
				break;
			case '(':
				t = Token::Type::lPara;
				break;
			case '+':
				t = Token::Type::Operator; prec = 2;
				break;
			case '-':
				t = Token::Type::Operator; prec = 2;
				break;
			case '/':
				t = Token::Type::Operator; prec = 3;
				break;
			case '*':
				t = Token::Type::Operator; prec = 3;
				break;
			case '^':
				t = Token::Type::Operator; ra = true; prec = 4;
			case '$':
				t = Token::Type::EndOfString;
				break;
			}
			std::string str = std::string(1, (*it));
			tokens.push_back(Token{ t,str,prec,ra });
		}
	}

	return tokens;
};