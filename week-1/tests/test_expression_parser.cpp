#include <gtest/gtest.h>
#include <stdexcept>
#include "expression_parser.h"

class ExpressionParserTest : public ::testing::Test {
protected:
    ExpressionParser parser;
};

// Basic expression parsing
TEST_F(ExpressionParserTest, ParsesSimpleAddition) {
    EXPECT_DOUBLE_EQ(parser.evaluate("2 + 3"), 5.0);
}

TEST_F(ExpressionParserTest, ParsesSimpleSubtraction) {
    EXPECT_DOUBLE_EQ(parser.evaluate("5 - 3"), 2.0);
}

TEST_F(ExpressionParserTest, ParsesSimpleMultiplication) {
    EXPECT_DOUBLE_EQ(parser.evaluate("4 * 5"), 20.0);
}

TEST_F(ExpressionParserTest, ParsesSimpleDivision) {
    EXPECT_DOUBLE_EQ(parser.evaluate("10 / 2"), 5.0);
}

// Operator precedence
TEST_F(ExpressionParserTest, RespectsOperatorPrecedence) {
    EXPECT_DOUBLE_EQ(parser.evaluate("2 + 3 * 4"), 14.0);
    EXPECT_DOUBLE_EQ(parser.evaluate("10 - 6 / 2"), 7.0);
}

// Parentheses
TEST_F(ExpressionParserTest, HandlesParentheses) {
    EXPECT_DOUBLE_EQ(parser.evaluate("(2 + 3) * 4"), 20.0);
    EXPECT_DOUBLE_EQ(parser.evaluate("2 * (3 + 4)"), 14.0);
    EXPECT_DOUBLE_EQ(parser.evaluate("((2 + 3) * 4) / 2"), 10.0);
}

// Complex expressions
TEST_F(ExpressionParserTest, ParsesComplexExpressions) {
    EXPECT_DOUBLE_EQ(parser.evaluate("2 + 3 * 4 - 5 / 2"), 11.5);
    EXPECT_DOUBLE_EQ(parser.evaluate("(2 + 3) * (4 - 1)"), 15.0);
}

// Negative numbers
TEST_F(ExpressionParserTest, HandlesNegativeNumbers) {
    EXPECT_DOUBLE_EQ(parser.evaluate("-5 + 3"), -2.0);
    EXPECT_DOUBLE_EQ(parser.evaluate("2 * -3"), -6.0);
    EXPECT_DOUBLE_EQ(parser.evaluate("(-2) + (-3)"), -5.0);
}

// Decimal numbers
TEST_F(ExpressionParserTest, HandlesDecimalNumbers) {
    EXPECT_NEAR(parser.evaluate("2.5 + 3.7"), 6.2, 1e-10);
    EXPECT_NEAR(parser.evaluate("1.5 * 2.0"), 3.0, 1e-10);
}

// Error handling
TEST_F(ExpressionParserTest, ThrowsOnInvalidExpression) {
    EXPECT_THROW(parser.evaluate("2 +"), std::invalid_argument);
    EXPECT_THROW(parser.evaluate("* 3"), std::invalid_argument);
    EXPECT_THROW(parser.evaluate("2 + + 3"), std::invalid_argument);
}

TEST_F(ExpressionParserTest, ThrowsOnMismatchedParentheses) {
    EXPECT_THROW(parser.evaluate("(2 + 3"), std::invalid_argument);
    EXPECT_THROW(parser.evaluate("2 + 3)"), std::invalid_argument);
    EXPECT_THROW(parser.evaluate("((2 + 3)"), std::invalid_argument);
}

TEST_F(ExpressionParserTest, ThrowsOnDivisionByZero) {
    EXPECT_THROW(parser.evaluate("5 / 0"), std::invalid_argument);
    EXPECT_THROW(parser.evaluate("10 / (2 - 2)"), std::invalid_argument);
}

// Whitespace handling
TEST_F(ExpressionParserTest, IgnoresWhitespace) {
    EXPECT_DOUBLE_EQ(parser.evaluate("  2  +  3  "), 5.0);
    EXPECT_DOUBLE_EQ(parser.evaluate("2+3"), 5.0);
    EXPECT_DOUBLE_EQ(parser.evaluate(" ( 2 + 3 ) * 4 "), 20.0);
}

// Functions
TEST_F(ExpressionParserTest, ParsesFunctions) {
    EXPECT_NEAR(parser.evaluate("sqrt(9)"), 3.0, 1e-10);
    EXPECT_NEAR(parser.evaluate("pow(2, 3)"), 8.0, 1e-10);
    EXPECT_NEAR(parser.evaluate("sin(0)"), 0.0, 1e-10);
    EXPECT_NEAR(parser.evaluate("cos(0)"), 1.0, 1e-10);
}

TEST_F(ExpressionParserTest, ParsesNestedFunctions) {
    EXPECT_NEAR(parser.evaluate("sqrt(pow(3, 2))"), 3.0, 1e-10);
    EXPECT_NEAR(parser.evaluate("pow(sqrt(16), 2)"), 16.0, 1e-10);
}
