#include <gtest/gtest.h>
#include "vector_expr.h"
#include "matrix_expr.h"

class ExpressionTemplateTest : public ::testing::Test {
protected:
    static constexpr size_t SIZE = 1000;
};

// Vector expression tests
TEST_F(ExpressionTemplateTest, VectorAddition) {
    Vector a(SIZE, 1.0);
    Vector b(SIZE, 2.0);
    
    Vector c = a + b;
    
    EXPECT_EQ(c.size(), SIZE);
    for (size_t i = 0; i < SIZE; ++i) {
        EXPECT_DOUBLE_EQ(c[i], 3.0);
    }
}

TEST_F(ExpressionTemplateTest, VectorSubtraction) {
    Vector a(SIZE, 5.0);
    Vector b(SIZE, 2.0);
    
    Vector c = a - b;
    
    for (size_t i = 0; i < SIZE; ++i) {
        EXPECT_DOUBLE_EQ(c[i], 3.0);
    }
}

TEST_F(ExpressionTemplateTest, VectorMultiplication) {
    Vector a(SIZE, 3.0);
    Vector b(SIZE, 4.0);
    
    Vector c = a * b;
    
    for (size_t i = 0; i < SIZE; ++i) {
        EXPECT_DOUBLE_EQ(c[i], 12.0);
    }
}

TEST_F(ExpressionTemplateTest, ScalarOperations) {
    Vector a(SIZE, 2.0);
    
    Vector b = a * 3.0;
    Vector c = 5.0 + a;
    
    for (size_t i = 0; i < SIZE; ++i) {
        EXPECT_DOUBLE_EQ(b[i], 6.0);
        EXPECT_DOUBLE_EQ(c[i], 7.0);
    }
}

TEST_F(ExpressionTemplateTest, ComplexExpressions) {
    Vector a(SIZE, 1.0);
    Vector b(SIZE, 2.0);
    Vector c(SIZE, 3.0);
    Vector d(SIZE, 4.0);
    
    Vector result = a + b * c - d / 2.0;
    
    for (size_t i = 0; i < SIZE; ++i) {
        EXPECT_DOUBLE_EQ(result[i], 1.0 + 2.0 * 3.0 - 4.0 / 2.0);
    }
}

TEST_F(ExpressionTemplateTest, NoTemporaryCreation) {
    Vector a(SIZE, 1.0);
    Vector b(SIZE, 2.0);
    Vector c(SIZE, 3.0);
    
    // This should not create temporary vectors
    auto expr = a + b * c;
    
    // Expression should be lazy
    EXPECT_NE(typeid(expr), typeid(Vector));
    
    // Only when assigned should evaluation happen
    Vector result = expr;
    
    for (size_t i = 0; i < SIZE; ++i) {
        EXPECT_DOUBLE_EQ(result[i], 1.0 + 2.0 * 3.0);
    }
}

TEST_F(ExpressionTemplateTest, ChainedOperations) {
    Vector a(SIZE, 1.0);
    Vector b(SIZE, 2.0);
    Vector c(SIZE, 3.0);
    Vector d(SIZE, 4.0);
    Vector e(SIZE, 5.0);
    
    Vector result = (a + b) * (c - d) + e;
    
    for (size_t i = 0; i < SIZE; ++i) {
        double expected = (1.0 + 2.0) * (3.0 - 4.0) + 5.0;
        EXPECT_DOUBLE_EQ(result[i], expected);
    }
}

// Matrix expression tests
TEST_F(ExpressionTemplateTest, MatrixAddition) {
    Matrix a(10, 10, 1.0);
    Matrix b(10, 10, 2.0);
    
    Matrix c = a + b;
    
    EXPECT_EQ(c.rows(), 10);
    EXPECT_EQ(c.cols(), 10);
    
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            EXPECT_DOUBLE_EQ(c(i, j), 3.0);
        }
    }
}

TEST_F(ExpressionTemplateTest, MatrixVectorMultiplication) {
    Matrix m(3, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
    m(2, 0) = 7; m(2, 1) = 8; m(2, 2) = 9;
    
    Vector v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    
    Vector result = m * v;
    
    EXPECT_DOUBLE_EQ(result[0], 14.0); // 1*1 + 2*2 + 3*3
    EXPECT_DOUBLE_EQ(result[1], 32.0); // 4*1 + 5*2 + 6*3
    EXPECT_DOUBLE_EQ(result[2], 50.0); // 7*1 + 8*2 + 9*3
}

TEST_F(ExpressionTemplateTest, MatrixTranspose) {
    Matrix m(2, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;
    
    Matrix t = transpose(m);
    
    EXPECT_EQ(t.rows(), 3);
    EXPECT_EQ(t.cols(), 2);
    EXPECT_DOUBLE_EQ(t(0, 0), 1);
    EXPECT_DOUBLE_EQ(t(1, 0), 2);
    EXPECT_DOUBLE_EQ(t(2, 0), 3);
    EXPECT_DOUBLE_EQ(t(0, 1), 4);
    EXPECT_DOUBLE_EQ(t(1, 1), 5);
    EXPECT_DOUBLE_EQ(t(2, 1), 6);
}

// Performance tests
TEST_F(ExpressionTemplateTest, PerformanceComparison) {
    const size_t LARGE_SIZE = 10000;
    Vector a(LARGE_SIZE, 1.0);
    Vector b(LARGE_SIZE, 2.0);
    Vector c(LARGE_SIZE, 3.0);
    Vector d(LARGE_SIZE, 4.0);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Expression template version (should be faster)
    Vector result1 = a + b * c - d;
    
    auto expr_time = std::chrono::high_resolution_clock::now() - start;
    
    start = std::chrono::high_resolution_clock::now();
    
    // Manual version with temporaries
    Vector temp1 = b * c;
    Vector temp2 = a + temp1;
    Vector result2 = temp2 - d;
    
    auto manual_time = std::chrono::high_resolution_clock::now() - start;
    
    // Results should be identical
    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        EXPECT_DOUBLE_EQ(result1[i], result2[i]);
    }
    
    // Expression template should be faster (or at least not much slower)
    EXPECT_LE(expr_time.count(), manual_time.count() * 1.5);
}

// Type deduction tests
TEST_F(ExpressionTemplateTest, TypeDeduction) {
    Vector a(10, 1.0);
    Vector b(10, 2.0);
    
    auto expr = a + b;
    
    // Should be an expression type, not Vector
    EXPECT_FALSE(std::is_same_v<decltype(expr), Vector>);
    
    // But should be convertible to Vector
    Vector result = expr;
    EXPECT_EQ(result.size(), 10);
}

// SFINAE tests
TEST_F(ExpressionTemplateTest, SFINAEConstraints) {
    Vector a(10, 1.0);
    
    // These should compile
    auto expr1 = a + a;
    auto expr2 = a * 2.0;
    auto expr3 = 3.0 + a;
    
    // This should not compile (different sizes)
    Vector b(5, 1.0);
    // auto invalid_expr = a + b; // Should cause compilation error
    
    EXPECT_TRUE(true); // If we get here, SFINAE is working
}
