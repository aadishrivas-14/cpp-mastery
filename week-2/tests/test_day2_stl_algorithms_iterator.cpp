#include "simple_iterator.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

TEST(Day2STLAlgorithmsTest, FindAlgorithm) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  auto it = std::find(vec.begin(), vec.end(), 3);
  EXPECT_NE(it, vec.end());
  EXPECT_EQ(*it, 3);
}

TEST(Day2STLAlgorithmsTest, SortAlgorithm) {
  std::vector<int> vec = {5, 2, 8, 1, 9};
  std::sort(vec.begin(), vec.end());
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[4], 9);
}

TEST(Day2IteratorTest, CustomIterator) {
  int arr[] = {1, 2, 3};
  SimpleIterator<int> it(arr);
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
