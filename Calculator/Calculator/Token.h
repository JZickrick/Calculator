#pragma once
#ifndef Token_H
#define Token_H

#include <vector>
#include <string>
//#include <iostream>

class Token { //what forms a token

public:
	enum class Type {
		Unknown,	//0
		Number,		//1
		Operator,	//2
		lPara,		//3
		rPara,		//4
		EndOfString,
	};
	Token(Type t, std::string& s, int prec = -1, bool ra = false)
		: type{ t }, str{ s }, precedence{ prec }, rightAssociative{ ra }
	{}
	int getPrec() { return precedence; }
	Type getType() { return type; }
	std::string getString() { return str; }
	bool getRightAssociative() { return rightAssociative; }

	Type type;//This represents how it should be read in evaluation
	std::string str; //This is what the collection of symbols are
	int precedence; //dont know if we need this yet.
	bool rightAssociative; // not sure why we need this one either

	/*
	std::ostream& operator<<(std::ostream& os, Token& token) { // allows us to use the << to write a tokem
		os << token.getString();
		return os;
	}
	*/

};

#endif