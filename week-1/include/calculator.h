#pragma once

/**
 * TODO: Implement a Basic Calculator
 * 
 * Requirements:
 * - add(a, b) - Return sum of two numbers
 * - subtract(a, b) - Return difference
 * - multiply(a, b) - Return product
 * - divide(a, b) - Return quotient
 * 
 * All methods should be const and take double parameters
 */

class Calculator {
 public:
  double add(double a, double b) const;
  double subtract(double a, double b) const;
  double multiply(double a, double b) const;
  double divide(double a, double b) const;
};
