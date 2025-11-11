// Week 1, Day 1: C++ Basics Setup + Calculator Project
// Project Status: Calculator with Expression Parser (Part 1)

#include "calculator.h"
#include <gtest/gtest.h>

TEST(Day1CalculatorTest, Addition) {
  Calculator calc;
  EXPECT_DOUBLE_EQ(calc.add(2, 3), 5);
  EXPECT_DOUBLE_EQ(calc.add(-1, 1), 0);
}

TEST(Day1CalculatorTest, Subtraction) {
  Calculator calc;
  EXPECT_DOUBLE_EQ(calc.subtract(5, 3), 2);
  EXPECT_DOUBLE_EQ(calc.subtract(0, 5), -5);
}

TEST(Day1CalculatorTest, Multiplication) {
  Calculator calc;
  EXPECT_DOUBLE_EQ(calc.multiply(4, 5), 20);
  EXPECT_DOUBLE_EQ(calc.multiply(-2, 3), -6);
}

TEST(Day1CalculatorTest, Division) {
  Calculator calc;
  EXPECT_DOUBLE_EQ(calc.divide(10, 2), 5);
  EXPECT_DOUBLE_EQ(calc.divide(7, 2), 3.5);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
