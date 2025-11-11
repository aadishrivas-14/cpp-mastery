// Week 1, Day 2: Control Flow + Expression Parser
// Project Status: Calculator with Expression Parser (Part 2)

#include "expression_parser.h"
#include <gtest/gtest.h>

TEST(Day2ExpressionParserTest, SimpleAddition) {
  ExpressionParser parser;
  EXPECT_DOUBLE_EQ(parser.evaluate("2+3"), 5);
}

TEST(Day2ExpressionParserTest, SimpleSubtraction) {
  ExpressionParser parser;
  EXPECT_DOUBLE_EQ(parser.evaluate("5-3"), 2);
}

TEST(Day2ExpressionParserTest, Multiplication) {
  ExpressionParser parser;
  EXPECT_DOUBLE_EQ(parser.evaluate("4*5"), 20);
}

TEST(Day2ExpressionParserTest, Division) {
  ExpressionParser parser;
  EXPECT_DOUBLE_EQ(parser.evaluate("10/2"), 5);
}

TEST(Day2ExpressionParserTest, ComplexExpression) {
  ExpressionParser parser;
  EXPECT_DOUBLE_EQ(parser.evaluate("2+3*4"), 14);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
