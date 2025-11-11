#include "bst.h"
#include <gtest/gtest.h>

TEST(Day5BSTTest, Insert) {
  BST<int> bst;
  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  EXPECT_EQ(bst.size(), 3);
}

TEST(Day5BSTTest, Find) {
  BST<int> bst;
  bst.insert(5);
  EXPECT_FALSE(bst.find(5));  // Will fail until implemented
}

TEST(Day5BSTTest, Empty) {
  BST<int> bst;
  EXPECT_TRUE(bst.empty());
  bst.insert(1);
  EXPECT_FALSE(bst.empty());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
