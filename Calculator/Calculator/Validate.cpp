#include "Validate.h"

//enumeration tokens to easily refer to non terminal characters
enum tokens {
	PLUS_TOKEN = 0, MIN_TOKEN = 1, MULT_TOKEN = 2, DIV_TOKEN = 3, EXP_TOKEN = 4, LP_TOKEN = 5, RP_TOKEN = 6, DOUBLE_TOKEN = 7,
	EOF_TOKEN = 8, t_NT = 0, T_NT = 1, r_NT = 2, R_NT = 3, w_NT = 4, W_NT = 5, v_NT = 6
};

bool validate(std::vector<Token>& math_exp) {
	//look-up table
	std::string ll_table[7][9] = {
		//+       -       *       /       ^       (       )       double  $
		 {""     ,""     ,""     ,""     ,""      ,"rT"   ,""     ,"rT"   ,"" },  // t->
		 {"+rT"  ,"-rT"  ,""     ,""     ,""      ,""     ,"e"    ,""     ,"e"},  // T->
		 {""     ,""     ,""     ,""     ,""      ,"wR"   ,""     ,"wR"   ,"" },  // r->
		 {"e"    ,"e"    ,"*wR"  ,"/wR"  ,""      ,""     ,"e"    ,""     ,"e"},  // R->
		 {""     ,""     ,""     ,""     ,""      ,"vW"   ,""     ,"vW"   ,"" },  // w
		 {"e"    ,"e"    ,"e"    ,"e"    ,"^vW"   ,""     ,"e"    ,""     ,"e"},  // W->
		 {""     ,""     ,""     ,""     ,""      ,"(t)"  ,""     ,"d"    ,"" }   // v->
	};

	//Adds double negative signs to the actual number (rather than having two negative signs)
	//Add implicit multiplication
	for (int i = 0; i < math_exp.size(); ++i) {
		Token::Type tempType = math_exp.at(i).getType();
		std::string tempTypeAsString = "";
		
		std::string tokenString = math_exp.at(i).getString();

		//negative numbers
		if (tempType == Token::Type::Operator && tokenString == "-") {
			Token::Type nextType = math_exp.at(i+1).getType();
			std::string nextString = math_exp.at(i+1).getString();
			//std::cout << "HERE" << std::endl;

			if (nextType == Token::Type::Operator && nextString == "-") {
				Token::Type nextNextType = math_exp.at(i + 2).getType();
				std::string nextNextString = math_exp.at(i + 2).getString();
				//std::cout << "HERE2" << std::endl;

				if (nextNextType == Token::Type::Number){
					std::string newString = "-" + nextNextString;
					Token newToken = { Token::Type::Number, newString };
					math_exp.at(i + 2) = newToken;
					math_exp.erase(math_exp.begin() + i + 1);
					//std::cout << "HERE 3" << std::endl;
				}
			}
		}

		//implicit multiplication
		if (tempType == Token::Type::rPara || tempType == Token::Type::Number) {
			Token::Type nextType = math_exp.at(i + 1).getType();
			//std::cout << "multiplication 1" << std::endl;

			if (nextType == Token::Type::lPara) {
				//vecOfNums.insert(itPos, 9);
				std::string multiplicationString = "*";
				Token multiplicationToken = { Token::Type::Operator, multiplicationString };
				math_exp.insert(math_exp.begin() + i + 1, multiplicationToken);
				i++;
				//std::cout << "multiplication 2" << std::endl;
			}
		}
	}

	//converts vector of tokens to string
	std::string math_exp_string = "";
	for (int i = 0; i < math_exp.size(); ++i) {
		Token::Type tempType = math_exp.at(i).getType();
		std::string tempTypeAsString = "";

		std::string tokenString = math_exp.at(i).getString();

		switch (tempType) {
		case Token::Type::Number:
			math_exp_string = math_exp_string + "d";
			break;
		case Token::Type::Operator:
			if (tokenString == "+") { math_exp_string = math_exp_string + "+"; }
			else if (tokenString == "-") { math_exp_string = math_exp_string + "-"; }
			else if (tokenString == "*") { math_exp_string = math_exp_string + "*"; }
			else if (tokenString == "/") { math_exp_string = math_exp_string + "/"; }
			else if (tokenString == "^") { math_exp_string = math_exp_string + "^"; }
			else {
				//adds invalid symbol
				math_exp_string = math_exp_string + tokenString;
			}
			break;
		case Token::Type::lPara:
			math_exp_string = math_exp_string + "(";
			break;
		case Token::Type::rPara:
			math_exp_string = math_exp_string + ")";
			break;
		case Token::Type::EndOfString:
			math_exp_string = math_exp_string + "$";
			break;
		case Token::Type::Unknown:
			math_exp_string = math_exp_string + tokenString;
			break;
		default: 
			math_exp_string = math_exp_string + tokenString;
			break;
		}
		//std::cout << math_exp_string << std::endl;
	}


	//Start processing string to validate

	std::stack<char> stack_machine;

	stack_machine.push('$');
	stack_machine.push('t');

	for (int i = 0; i < math_exp.size(); i++) {
		int next_token;
		int current_nonterminal;
		char string_char = math_exp_string.at(i);
		char stack_char = stack_machine.top();
		stack_machine.pop();

		switch (string_char) {
		case '+': next_token = PLUS_TOKEN; break;
		case '-': next_token = MIN_TOKEN; break;
		case '*': next_token = MULT_TOKEN; break;
		case '/': next_token = DIV_TOKEN; break;
		case '(': next_token = LP_TOKEN; break;
		case ')': next_token = RP_TOKEN; break;
		case 'd': next_token = DOUBLE_TOKEN; break;
		case '$': next_token = EOF_TOKEN; break;
		default:
			std::cout << "Error in input string. Invalid character entered: " << string_char << std::endl;
			std::cout << "Error occured at: " << math_exp_string.substr(0, i) << " ^ " << math_exp_string.substr(i, math_exp_string.length() - 1) << std::endl;
			return false;
		}

		while (string_char != stack_char) {
			std::string push_string = "";
			switch (stack_char) {
			case 't': current_nonterminal = t_NT; break;
			case 'T': current_nonterminal = T_NT; break;
			case 'r': current_nonterminal = r_NT; break;
			case 'R': current_nonterminal = R_NT; break;
			case 'w': current_nonterminal = w_NT; break;
			case 'W': current_nonterminal = W_NT; break;
			case 'v': current_nonterminal = v_NT; break;
			default:
				std::cout << "Invalid nonterminal: " << stack_char << std::endl;
				std::cout << "Error occured at: " << math_exp_string.substr(0, i) << " ^ " << math_exp_string.substr(i, math_exp_string.length() - 1) << std::endl;
				return false;
			}

			push_string = ll_table[current_nonterminal][next_token];
			//std::cout << current_nonterminal << " " << next_token << std::endl;


			if (push_string.length() == 0) {
				std::cout << "String is not expression!" << std::endl;
				std::cout << "Error occured at: " << math_exp_string.substr(0, i) << " ^ " << math_exp_string.substr(i, math_exp_string.length() - 1) << std::endl;
				return false;
			}

			if (push_string.empty()) {
				std::cout << "String is not expression!" << std::endl;
				std::cout << "Error occured at: " << math_exp_string.substr(0, i) << " ^ " << math_exp_string.substr(i, math_exp_string.length() - 1) << std::endl;
				return false;
			}

			if (push_string.at(0) != 'e') {
				for (int j = push_string.length() - 1; j >= 0; j--) {
					stack_machine.push(push_string.at(j));
				}
			}

			stack_char = stack_machine.top();
			stack_machine.pop();
		}
	}

	if (stack_machine.empty()) {
		return true;
	}
	else {
		return false;
	}
};
