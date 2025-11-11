#include <gtest/gtest.h>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        calc = std::make_unique<Calculator>();
    }
    
    std::unique_ptr<Calculator> calc;
};

// Basic arithmetic tests
TEST_F(CalculatorTest, AddsTwoPositiveNumbers) {
    EXPECT_EQ(calc->add(2, 3), 5);
}

TEST_F(CalculatorTest, AddsNegativeNumbers) {
    EXPECT_EQ(calc->add(-2, -3), -5);
}

TEST_F(CalculatorTest, AddsMixedNumbers) {
    EXPECT_EQ(calc->add(-2, 3), 1);
}

TEST_F(CalculatorTest, SubtractsTwoNumbers) {
    EXPECT_EQ(calc->subtract(5, 3), 2);
}

TEST_F(CalculatorTest, MultipliesTwoNumbers) {
    EXPECT_EQ(calc->multiply(4, 5), 20);
}

TEST_F(CalculatorTest, DividesTwoNumbers) {
    EXPECT_DOUBLE_EQ(calc->divide(10, 2), 5.0);
}

TEST_F(CalculatorTest, ThrowsOnDivisionByZero) {
    EXPECT_THROW(calc->divide(10, 0), std::invalid_argument);
}

// Parameterized tests for comprehensive coverage
class CalculatorParameterizedTest : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(CalculatorParameterizedTest, Addition) {
    auto [a, b, expected] = GetParam();
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.add(a, b), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AdditionTests,
    CalculatorParameterizedTest,
    ::testing::Values(
        std::make_tuple(0, 0, 0),
        std::make_tuple(1, 1, 2),
        std::make_tuple(-1, 1, 0),
        std::make_tuple(3.14, 2.86, 6.0),
        std::make_tuple(1e6, 1e6, 2e6)
    )
);

// Edge cases and error handling
TEST_F(CalculatorTest, HandlesLargeNumbers) {
    EXPECT_NO_THROW(calc->add(1e15, 1e15));
}

TEST_F(CalculatorTest, HandlesFloatingPointPrecision) {
    double result = calc->add(0.1, 0.2);
    EXPECT_NEAR(result, 0.3, 1e-10);
}
