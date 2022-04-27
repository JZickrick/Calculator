#pragma once
#ifndef Validate_H
#define Validate_H

#include <iostream>
#include <string>
#include <stack>
#include <regex>
#include <iterator>
#include "Token.h"

enum tokens;
bool validate(std::vector<Token>& math_exp);

#endif