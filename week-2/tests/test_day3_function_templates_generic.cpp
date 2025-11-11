#include "templates.h"
#include <gtest/gtest.h>

TEST(Day3FunctionTemplatesTest, MaxFunction) {
  EXPECT_EQ(max(3, 5), 5);
  EXPECT_EQ(max(3.5, 2.1), 3.5);
}

TEST(Day3FunctionTemplatesTest, SwapFunction) {
  int a = 5, b = 10;
  swap(a, b);
  EXPECT_EQ(a, 10);
  EXPECT_EQ(b, 5);
}

TEST(Day3GenericLibraryTest, ArrayContainer) {
  Array<int, 5> arr;
  arr[0] = 10;
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr.size(), 5);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
