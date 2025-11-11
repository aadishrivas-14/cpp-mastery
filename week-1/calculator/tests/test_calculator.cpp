#include <gtest/gtest.h>
#include <stdexcept>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
};

// Basic arithmetic operations
TEST_F(CalculatorTest, AddsTwoPositiveNumbers) {
    EXPECT_EQ(calc.add(2, 3), 5);
}

TEST_F(CalculatorTest, AddsNegativeNumbers) {
    EXPECT_EQ(calc.add(-2, -3), -5);
}

TEST_F(CalculatorTest, AddsMixedNumbers) {
    EXPECT_EQ(calc.add(-2, 3), 1);
}

TEST_F(CalculatorTest, AddsZero) {
    EXPECT_EQ(calc.add(5, 0), 5);
    EXPECT_EQ(calc.add(0, 5), 5);
}

TEST_F(CalculatorTest, SubtractsTwoNumbers) {
    EXPECT_EQ(calc.subtract(5, 3), 2);
    EXPECT_EQ(calc.subtract(3, 5), -2);
}

TEST_F(CalculatorTest, MultipliesTwoNumbers) {
    EXPECT_EQ(calc.multiply(4, 5), 20);
    EXPECT_EQ(calc.multiply(-4, 5), -20);
    EXPECT_EQ(calc.multiply(0, 5), 0);
}

TEST_F(CalculatorTest, DividesTwoNumbers) {
    EXPECT_DOUBLE_EQ(calc.divide(10, 2), 5.0);
    EXPECT_DOUBLE_EQ(calc.divide(7, 2), 3.5);
}

TEST_F(CalculatorTest, ThrowsOnDivisionByZero) {
    EXPECT_THROW(calc.divide(10, 0), std::invalid_argument);
}

TEST_F(CalculatorTest, HandlesFloatingPointPrecision) {
    double result = calc.add(0.1, 0.2);
    EXPECT_NEAR(result, 0.3, 1e-10);
}

TEST_F(CalculatorTest, HandlesLargeNumbers) {
    EXPECT_NO_THROW(calc.add(1e15, 1e15));
    EXPECT_EQ(calc.multiply(1000000, 1000000), 1000000000000LL);
}

// Power function tests
TEST_F(CalculatorTest, CalculatesPower) {
    EXPECT_DOUBLE_EQ(calc.power(2, 3), 8.0);
    EXPECT_DOUBLE_EQ(calc.power(5, 0), 1.0);
    EXPECT_DOUBLE_EQ(calc.power(2, -2), 0.25);
}

// Square root tests
TEST_F(CalculatorTest, CalculatesSquareRoot) {
    EXPECT_DOUBLE_EQ(calc.sqrt(9), 3.0);
    EXPECT_DOUBLE_EQ(calc.sqrt(0), 0.0);
    EXPECT_THROW(calc.sqrt(-1), std::invalid_argument);
}

// Factorial tests
TEST_F(CalculatorTest, CalculatesFactorial) {
    EXPECT_EQ(calc.factorial(0), 1);
    EXPECT_EQ(calc.factorial(5), 120);
    EXPECT_THROW(calc.factorial(-1), std::invalid_argument);
}

// Memory tests
TEST_F(CalculatorTest, StoresAndRecallsMemory) {
    calc.memoryStore(42.5);
    EXPECT_DOUBLE_EQ(calc.memoryRecall(), 42.5);
    
    calc.memoryAdd(7.5);
    EXPECT_DOUBLE_EQ(calc.memoryRecall(), 50.0);
    
    calc.memoryClear();
    EXPECT_DOUBLE_EQ(calc.memoryRecall(), 0.0);
}
