#include <iostream>
#include <string>
#include <stack>
#include <regex>

//enumeration tokens to easily refer to non terminal characters
enum tokens {
	PLUS_TOKEN = 0, MIN_TOKEN = 1, MULT_TOKEN = 2, DIV_TOKEN = 3, LP_TOKEN = 4, RP_TOKEN = 5, DOUBLE_TOKEN = 6,
	EOF_TOKEN = 7, t_NT = 0, T_NT = 1, r_NT = 2, R_NT = 3, v_NT = 4
};

bool validate(std::string math_exp) {

	//look-up table
	std::string ll_table[5][8] = {
		//+       -       *       /       (       )       double  $
		 {""     ,""     ,""     ,""     ,"rT"   ,""     ,"rT"   ,""},  // t->
		 {"+rT"  ,"-rT"  ,""     ,""     ,""     ,"e"    ,""     ,"e"}, // T->
		 {""     ,""     ,""     ,""     ,"vR"   ,""     ,"vR"   ,""},  // r->
		 {"e"    ,"e"    ,"*vR"  ,"/vR"  ,""     ,"e"    ,""     ,"e"}, // R->
		 {""     ,""     ,""     ,""     ,"(t)"  ,""     ,"d"    ,""}   // v->
	};

	std::string math_exp_regex = "";
	std::stack<char> stack_machine;
	std::regex double_pattern("(\\d+\\.?\\d*|\\.\\d+)");	//Converts numbers to the character d
	std::regex negative_pattern("(([+\\-*\\/]|^)\\-d)");	//Finds any negativ d's and drops the negative sign since processing is allowed on negative numbers
	std::regex implicit_parentheses("((d|\\))(\\())");		//Adds multiplication symbol between implicit multiplication

	//regex_replace(string, regex, replace string);
	math_exp_regex = regex_replace(math_exp, double_pattern, "d");
	math_exp_regex = regex_replace(math_exp_regex, negative_pattern, "$2d");
	math_exp_regex = regex_replace(math_exp_regex, implicit_parentheses, "$2*$3");

	//std::cout << math_exp_regex << std::endl << std::endl;

	math_exp_regex.append("$");

	stack_machine.push('$');
	stack_machine.push('t');

	for (int i = 0; i < math_exp_regex.length(); i++) {
		int next_token;
		int current_nonterminal;
		char string_char = math_exp_regex.at(i);
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
			std::cout << "Error occured at: " << math_exp_regex.substr(0, i) << " ^ " << math_exp_regex.substr(i, math_exp_regex.length() - 1) << std::endl;
			return false;
		}

		while (string_char != stack_char) {
			std::string push_string = "";
			switch (stack_char) {
			case 't': current_nonterminal = t_NT; break;
			case 'T': current_nonterminal = T_NT; break;
			case 'r': current_nonterminal = r_NT; break;
			case 'R': current_nonterminal = R_NT; break;
			case 'v': current_nonterminal = v_NT; break;
			default:
				std::cout << "Invalid nonterminal: " << stack_char << std::endl;
				std::cout << "Error occured at: " << math_exp_regex.substr(0, i) << " ^ " << math_exp_regex.substr(i, math_exp_regex.length() - 1) << std::endl;
				return false;
			}

			push_string = ll_table[current_nonterminal][next_token];


			if (push_string.length() == 0) {
				std::cout << "String is not expression!" << std::endl;
				std::cout << "Error occured at: " << math_exp_regex.substr(0, i) << " ^ " << math_exp_regex.substr(i, math_exp_regex.length() - 1) << std::endl;
				return false;
			}

			if (push_string.empty()) {
				std::cout << "String is not expression!" << std::endl;
				std::cout << "Error occured at: " << math_exp_regex.substr(0, i) << " ^ " << math_exp_regex.substr(i, math_exp_regex.length() - 1) << std::endl;
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
}