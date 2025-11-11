#pragma once

#include <string>

/**
 * TODO: Implement an Expression Parser
 * 
 * Requirements:
 * - evaluate(expr) - Parse and evaluate arithmetic expressions
 * - Support: +, -, *, / operators
 * - Handle operator precedence (* and / before + and -)
 * - No parentheses needed for basic version
 * 
 * Test cases:
 * - "2+3" should return 5
 * - "5-3" should return 2
 * - "4*5" should return 20
 * - "10/2" should return 5
 * - "2+3*4" should return 14 (not 20!)
 * 
 * Implementation hints:
 * - Parse string character by character
 * - Build numbers from digit characters
 * - Handle operator precedence (use two passes or stack)
 * - Consider using recursive descent parser
 */

class ExpressionParser {
 public:
  double evaluate(const std::string& expr);
};
