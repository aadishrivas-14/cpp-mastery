#include "../include/problems.h"
#include <gtest/gtest.h>

TEST(Problem16_ThreeSum, Basic) {
  std::vector<int> nums = {-1,0,1,2,-1,-4};
  auto result = threeSum(nums);
  EXPECT_EQ(result.size(), 2);
}

TEST(Problem17_GroupAnagrams, Basic) {
  std::vector<std::string> strs = {"eat","tea","tan","ate","nat","bat"};
  auto result = groupAnagrams(strs);
  EXPECT_EQ(result.size(), 3);
}

TEST(Problem18_LongestSubstring, Basic) {
  EXPECT_EQ(lengthOfLongestSubstring("abcabcbb"), 3);
  EXPECT_EQ(lengthOfLongestSubstring("bbbbb"), 1);
  EXPECT_EQ(lengthOfLongestSubstring("pwwkew"), 3);
}

TEST(Problem19_MaxArea, Basic) {
  EXPECT_EQ(maxArea({1,8,6,2,5,4,8,3,7}), 49);
  EXPECT_EQ(maxArea({1,1}), 1);
}

TEST(Problem20_ProductExceptSelf, Basic) {
  auto result = productExceptSelf({1,2,3,4});
  EXPECT_EQ(result, std::vector<int>({24,12,8,6}));
}

TEST(Problem21_RotateImage, Basic) {
  std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
  rotate(matrix);
  EXPECT_EQ(matrix[0][0], 7);
  EXPECT_EQ(matrix[0][2], 1);
}

TEST(Problem22_SpiralMatrix, Basic) {
  std::vector<std::vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
  auto result = spiralOrder(matrix);
  EXPECT_EQ(result, std::vector<int>({1,2,3,6,9,8,7,4,5}));
}

TEST(Problem23_JumpGame, Basic) {
  EXPECT_TRUE(canJump({2,3,1,1,4}));
  EXPECT_FALSE(canJump({3,2,1,0,4}));
}

TEST(Problem24_MergeIntervals, Basic) {
  std::vector<std::vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
  auto result = merge(intervals);
  EXPECT_EQ(result.size(), 3);
}

TEST(Problem25_UniquePaths, Basic) {
  EXPECT_EQ(uniquePaths(3, 7), 28);
  EXPECT_EQ(uniquePaths(3, 2), 3);
}

TEST(Problem26_CoinChange, Basic) {
  EXPECT_EQ(coinChange({1,2,5}, 11), 3);
  EXPECT_EQ(coinChange({2}, 3), -1);
}

TEST(Problem27_LIS, Basic) {
  EXPECT_EQ(lengthOfLIS({10,9,2,5,3,7,101,18}), 4);
  EXPECT_EQ(lengthOfLIS({0,1,0,3,2,3}), 4);
}

TEST(Problem28_WordBreak, Basic) {
  EXPECT_TRUE(wordBreak("leetcode", {"leet","code"}));
  EXPECT_FALSE(wordBreak("catsandog", {"cats","dog","sand","and","cat"}));
}

TEST(Problem29_HouseRobber2, Basic) {
  EXPECT_EQ(rob({2,3,2}), 3);
  EXPECT_EQ(rob({1,2,3,1}), 4);
}

TEST(Problem30_NumIslands, Basic) {
  std::vector<std::vector<char>> grid = {
    {'1','1','0','0','0'},
    {'1','1','0','0','0'},
    {'0','0','1','0','0'},
    {'0','0','0','1','1'}
  };
  EXPECT_EQ(numIslands(grid), 3);
}

TEST(Problem31_CourseSchedule, Basic) {
  std::vector<std::vector<int>> pre1 = {{1,0}};
  EXPECT_TRUE(canFinish(2, pre1));
  std::vector<std::vector<int>> pre2 = {{1,0},{0,1}};
  EXPECT_FALSE(canFinish(2, pre2));
}

TEST(Problem32_Trie, Basic) {
  Trie trie;
  trie.insert("apple");
  EXPECT_TRUE(trie.search("apple"));
  EXPECT_FALSE(trie.search("app"));
  EXPECT_TRUE(trie.startsWith("app"));
}

TEST(Problem33_KthLargest, Basic) {
  std::vector<int> nums = {3,2,1,5,6,4};
  EXPECT_EQ(findKthLargest(nums, 2), 5);
}

TEST(Problem34_TopKFrequent, Basic) {
  auto result = topKFrequent({1,1,1,2,2,3}, 2);
  EXPECT_EQ(result.size(), 2);
}

TEST(Problem35_FindPeak, Basic) {
  EXPECT_GE(findPeakElement({1,2,3,1}), 0);
  EXPECT_GE(findPeakElement({1,2,1,3,5,6,4}), 0);
}

TEST(Problem36_SearchRotated, Basic) {
  EXPECT_EQ(search({4,5,6,7,0,1,2}, 0), 4);
  EXPECT_EQ(search({4,5,6,7,0,1,2}, 3), -1);
}

TEST(Problem37_LevelOrder, Basic) {
  TreeNode* root = new TreeNode(3);
  root->left = new TreeNode(9);
  root->right = new TreeNode(20);
  auto result = levelOrder(root);
  EXPECT_EQ(result.size(), 2);
}

TEST(Problem38_ValidBST, Basic) {
  TreeNode* root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);
  EXPECT_TRUE(isValidBST(root));
}

TEST(Problem39_LCA, Basic) {
  TreeNode* root = new TreeNode(3);
  root->left = new TreeNode(5);
  root->right = new TreeNode(1);
  auto lca = lowestCommonAncestor(root, root->left, root->right);
  EXPECT_EQ(lca->val, 3);
}

TEST(Problem40_BuildTree, Basic) {
  std::vector<int> preorder = {3,9,20,15,7};
  std::vector<int> inorder = {9,3,15,20,7};
  auto root = buildTree(preorder, inorder);
  EXPECT_EQ(root->val, 3);
  EXPECT_EQ(root->left->val, 9);
}
