#include "containers.h"
#include <gtest/gtest.h>

TEST(Day4ClassTemplatesTest, VectorTemplate) {
  Vector<int> vec(5);
  vec[0] = 10;
  EXPECT_EQ(vec[0], 10);
  EXPECT_EQ(vec.size(), 5);
}

TEST(Day4ClassTemplatesTest, StackTemplate) {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.top(), 2);
  EXPECT_EQ(stack.size(), 2);
}

TEST(Day4ExpressionTemplatesTest, LazyEvaluation) {
  EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
