#include "expression_parser.h"
#include <vector>
#include <string>

//## Algorithm Name
//
//This is a simplified version of "Operator Precedence Parsing" or "Two-Pass Expression Evaluation".
//
//More advanced versions:
//• *Shunting Yard Algorithm** (Dijkstra) - handles parentheses
//• **Recursive Descent Parser** - more flexible
//• **Abstract Syntax Tree (AST)** - used in compilers


// 'double' is return type, 'const std::string&' means reference (no copy)
double ExpressionParser::evaluate(const std::string& expr) {
  std::vector<double> numbers;
  std::vector<char> operators;

  // Step 1: Parse expression into numbers and operators
  std::string current_number = "";
  for (size_t i = 0; i < expr.length(); i++) {
    char c = expr[i];

    if (c >= '0' && c <= '9') {
      current_number += c;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      // std::stod = string to double conversion
      numbers.push_back(std::stod(current_number));
      operators.push_back(c);
      current_number = "";
    }
  }
  // Don't forget the last number
  numbers.push_back(std::stod(current_number));

  // Step 2: First pass - handle * and /
  size_t i = 0;
  while (i < operators.size()) {
    if (operators[i] == '*' || operators[i] == '/') {
      double left = numbers[i];
      double right = numbers[i + 1];
      double result;

      if (operators[i] == '*') {
        result = left * right;
      } else {
        result = left / right;
      }

      // Replace: remove left, right, operator; insert result
      numbers.erase(numbers.begin() + i);
      numbers.erase(numbers.begin() + i);
      numbers.insert(numbers.begin() + i, result);
      operators.erase(operators.begin() + i);
      // Don't increment i, check same position again
    } else {
      i++;
    }
  }

  // Step 3: Second pass - handle + and -
  double result = numbers[0];
  for (size_t i = 0; i < operators.size(); i++) {
    if (operators[i] == '+') {
      result += numbers[i + 1];
    } else if (operators[i] == '-') {
      result -= numbers[i + 1];
    }
  }

  return result;
}