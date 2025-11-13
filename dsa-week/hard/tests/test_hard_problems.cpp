#include "../include/problems.h"
#include <gtest/gtest.h>

TEST(Problem41_MedianSortedArrays, Basic) {
  EXPECT_DOUBLE_EQ(findMedianSortedArrays({1,3}, {2}), 2.0);
  EXPECT_DOUBLE_EQ(findMedianSortedArrays({1,2}, {3,4}), 2.5);
}

TEST(Problem42_TrappingRainWater, Basic) {
  EXPECT_EQ(trap({0,1,0,2,1,0,1,3,2,1,2,1}), 6);
  EXPECT_EQ(trap({4,2,0,3,2,5}), 9);
}

TEST(Problem43_LongestValidParentheses, Basic) {
  EXPECT_EQ(longestValidParentheses("(()"), 2);
  EXPECT_EQ(longestValidParentheses(")()())"), 4);
  EXPECT_EQ(longestValidParentheses(""), 0);
}

TEST(Problem44_WildcardMatching, Basic) {
  EXPECT_FALSE(isMatch("aa", "a"));
  EXPECT_TRUE(isMatch("aa", "*"));
  EXPECT_FALSE(isMatch("cb", "?a"));
  EXPECT_TRUE(isMatch("adceb", "*a*b"));
}

TEST(Problem45_EditDistance, Basic) {
  EXPECT_EQ(minDistance("horse", "ros"), 3);
  EXPECT_EQ(minDistance("intention", "execution"), 5);
}

TEST(Problem46_MergeKLists, Basic) {
  ListNode* l1 = new ListNode(1);
  l1->next = new ListNode(4);
  ListNode* l2 = new ListNode(1);
  l2->next = new ListNode(3);
  ListNode* l3 = new ListNode(2);
  std::vector<ListNode*> lists = {l1, l2, l3};
  auto result = mergeKLists(lists);
  EXPECT_EQ(result->val, 1);
}

TEST(Problem47_LargestRectangle, Basic) {
  EXPECT_EQ(largestRectangleArea({2,1,5,6,2,3}), 10);
  EXPECT_EQ(largestRectangleArea({2,4}), 4);
}

TEST(Problem48_MaximalRectangle, Basic) {
  std::vector<std::vector<char>> matrix = {
    {'1','0','1','0','0'},
    {'1','0','1','1','1'},
    {'1','1','1','1','1'},
    {'1','0','0','1','0'}
  };
  EXPECT_EQ(maximalRectangle(matrix), 6);
}

TEST(Problem49_WordLadder, Basic) {
  std::vector<std::string> wordList = {"hot","dot","dog","lot","log","cog"};
  EXPECT_EQ(ladderLength("hit", "cog", wordList), 5);
}

TEST(Problem50_SerializeDeserialize, Basic) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->right->left = new TreeNode(4);
  root->right->right = new TreeNode(5);
  
  Codec codec;
  std::string serialized = codec.serialize(root);
  TreeNode* deserialized = codec.deserialize(serialized);
  
  EXPECT_EQ(deserialized->val, 1);
  EXPECT_EQ(deserialized->left->val, 2);
  EXPECT_EQ(deserialized->right->val, 3);
}
