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
 * 
 * 
The compiler doesn't know:
• What is Calculator?
• Is add a method of this class?
• What are the parameter types?
• Is it const?

## The Header is Essential Because:

1. Declares the class structure - tells compiler what Calculator is
2. Declares method signatures - tells compiler what methods exist
3. Shared between files - both .cpp and test files need it
4. Enables separate compilation - files can be compiled independently

## Bottom Line:
 */

class Calculator {
 public:
  double add(double a, double b) const;
  double subtract(double a, double b) const;
  double multiply(double a, double b) const;
  double divide(double a, double b) const;
};
