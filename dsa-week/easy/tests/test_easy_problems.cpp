#include "../include/problems.h"
#include <gtest/gtest.h>
#include <algorithm>

// ============================================================================
// Problem 1: Two Sum
// Company: Amazon, Google, Meta
// ============================================================================
TEST(Problem01_TwoSum, BasicCase) {
  std::vector<int> nums = {2, 7, 11, 15};
  auto result = twoSum(nums, 9);
  std::sort(result.begin(), result.end());
  EXPECT_EQ(result, std::vector<int>({0, 1}));
}

TEST(Problem01_TwoSum, MultipleValid) {
  std::vector<int> nums = {3, 2, 4};
  auto result = twoSum(nums, 6);
  std::sort(result.begin(), result.end());
  EXPECT_EQ(result, std::vector<int>({1, 2}));
}

TEST(Problem01_TwoSum, SameNumber) {
  std::vector<int> nums = {3, 3};
  auto result = twoSum(nums, 6);
  EXPECT_EQ(result.size(), 2);
}

// ============================================================================
// Problem 2: Valid Parentheses
// Company: Microsoft, Meta, Amazon
// ============================================================================
TEST(Problem02_ValidParentheses, ValidSimple) {
  EXPECT_TRUE(isValidParentheses("()"));
  EXPECT_TRUE(isValidParentheses("()[]{}"));
  EXPECT_TRUE(isValidParentheses("{[]}"));
}

TEST(Problem02_ValidParentheses, Invalid) {
  EXPECT_FALSE(isValidParentheses("(]"));
  EXPECT_FALSE(isValidParentheses("([)]"));
  EXPECT_FALSE(isValidParentheses("(("));
}

TEST(Problem02_ValidParentheses, EdgeCases) {
  EXPECT_TRUE(isValidParentheses(""));
  EXPECT_FALSE(isValidParentheses("("));
  EXPECT_FALSE(isValidParentheses(")"));
}

// ============================================================================
// Problem 3: Merge Two Sorted Lists
// Company: Amazon, Apple, Microsoft
// ============================================================================
TEST(Problem03_MergeLists, BothNonEmpty) {
  ListNode* l1 = new ListNode(1);
  l1->next = new ListNode(2);
  l1->next->next = new ListNode(4);
  
  ListNode* l2 = new ListNode(1);
  l2->next = new ListNode(3);
  l2->next->next = new ListNode(4);
  
  ListNode* result = mergeTwoLists(l1, l2);
  
  std::vector<int> expected = {1, 1, 2, 3, 4, 4};
  int i = 0;
  while (result) {
    EXPECT_EQ(result->val, expected[i++]);
    ListNode* temp = result;
    result = result->next;
    delete temp;
  }
}

TEST(Problem03_MergeLists, OneEmpty) {
  ListNode* l1 = nullptr;
  ListNode* l2 = new ListNode(0);
  
  ListNode* result = mergeTwoLists(l1, l2);
  EXPECT_EQ(result->val, 0);
  delete result;
}

// ============================================================================
// Problem 4: Best Time to Buy and Sell Stock
// Company: Amazon, Bloomberg, Microsoft
// ============================================================================
TEST(Problem04_MaxProfit, NormalCase) {
  EXPECT_EQ(maxProfit({7, 1, 5, 3, 6, 4}), 5);
}

TEST(Problem04_MaxProfit, NoProfit) {
  EXPECT_EQ(maxProfit({7, 6, 4, 3, 1}), 0);
}

TEST(Problem04_MaxProfit, SingleDay) {
  EXPECT_EQ(maxProfit({5}), 0);
}

// ============================================================================
// Problem 5: Valid Palindrome
// Company: Meta, Microsoft, Amazon
// ============================================================================
TEST(Problem05_Palindrome, ValidCases) {
  EXPECT_TRUE(isPalindrome("A man, a plan, a canal: Panama"));
  EXPECT_TRUE(isPalindrome("race a car") == false);
  EXPECT_TRUE(isPalindrome(" "));
}

TEST(Problem05_Palindrome, EdgeCases) {
  EXPECT_TRUE(isPalindrome(""));
  EXPECT_TRUE(isPalindrome("a"));
  EXPECT_TRUE(isPalindrome("aa"));
}

// ============================================================================
// Problem 6: Maximum Subarray (Kadane's Algorithm)
// Company: Amazon, Google, Microsoft
// ============================================================================
TEST(Problem06_MaxSubarray, MixedNumbers) {
  EXPECT_EQ(maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}), 6);
}

TEST(Problem06_MaxSubarray, AllPositive) {
  EXPECT_EQ(maxSubArray({1, 2, 3, 4, 5}), 15);
}

TEST(Problem06_MaxSubarray, AllNegative) {
  EXPECT_EQ(maxSubArray({-5, -2, -3, -1}), -1);
}

TEST(Problem06_MaxSubarray, SingleElement) {
  EXPECT_EQ(maxSubArray({5}), 5);
}

// ============================================================================
// Problem 7: Contains Duplicate
// Company: Apple, Adobe, Amazon
// ============================================================================
TEST(Problem07_ContainsDuplicate, HasDuplicate) {
  EXPECT_TRUE(containsDuplicate({1, 2, 3, 1}));
  EXPECT_TRUE(containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}));
}

TEST(Problem07_ContainsDuplicate, NoDuplicate) {
  EXPECT_FALSE(containsDuplicate({1, 2, 3, 4}));
}

// ============================================================================
// Problem 8: Reverse Linked List
// Company: Amazon, Microsoft, Meta
// ============================================================================
TEST(Problem08_ReverseList, NormalCase) {
  ListNode* head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  
  ListNode* reversed = reverseList(head);
  
  EXPECT_EQ(reversed->val, 3);
  EXPECT_EQ(reversed->next->val, 2);
  EXPECT_EQ(reversed->next->next->val, 1);
  
  // Cleanup
  while (reversed) {
    ListNode* temp = reversed;
    reversed = reversed->next;
    delete temp;
  }
}

TEST(Problem08_ReverseList, EmptyList) {
  EXPECT_EQ(reverseList(nullptr), nullptr);
}

// ============================================================================
// Problem 9: Binary Search
// Company: Google, Meta, Amazon
// ============================================================================
TEST(Problem09_BinarySearch, Found) {
  EXPECT_EQ(binarySearch({-1, 0, 3, 5, 9, 12}, 9), 4);
  EXPECT_EQ(binarySearch({-1, 0, 3, 5, 9, 12}, -1), 0);
}

TEST(Problem09_BinarySearch, NotFound) {
  EXPECT_EQ(binarySearch({-1, 0, 3, 5, 9, 12}, 2), -1);
}

// ============================================================================
// Problem 10: Climbing Stairs
// Company: Amazon, Adobe, Google
// ============================================================================
TEST(Problem10_ClimbingStairs, SmallCases) {
  EXPECT_EQ(climbStairs(2), 2);
  EXPECT_EQ(climbStairs(3), 3);
  EXPECT_EQ(climbStairs(4), 5);
}

TEST(Problem10_ClimbingStairs, LargerCase) {
  EXPECT_EQ(climbStairs(5), 8);
  EXPECT_EQ(climbStairs(10), 89);
}

// ============================================================================
// Problem 11: Symmetric Tree
// Company: Microsoft, Amazon, Meta
// ============================================================================
TEST(Problem11_SymmetricTree, Symmetric) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(2);
  root->left->left = new TreeNode(3);
  root->left->right = new TreeNode(4);
  root->right->left = new TreeNode(4);
  root->right->right = new TreeNode(3);
  
  EXPECT_TRUE(isSymmetric(root));
  
  // Cleanup (simplified)
  delete root->left->left;
  delete root->left->right;
  delete root->right->left;
  delete root->right->right;
  delete root->left;
  delete root->right;
  delete root;
}

TEST(Problem11_SymmetricTree, NotSymmetric) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(2);
  root->left->right = new TreeNode(3);
  root->right->right = new TreeNode(3);
  
  EXPECT_FALSE(isSymmetric(root));
  
  delete root->left->right;
  delete root->right->right;
  delete root->left;
  delete root->right;
  delete root;
}

// ============================================================================
// Problem 12: Single Number
// Company: Google, Apple, Amazon
// ============================================================================
TEST(Problem12_SingleNumber, BasicCase) {
  EXPECT_EQ(singleNumber({2, 2, 1}), 1);
  EXPECT_EQ(singleNumber({4, 1, 2, 1, 2}), 4);
}

TEST(Problem12_SingleNumber, SingleElement) {
  EXPECT_EQ(singleNumber({1}), 1);
}

// ============================================================================
// Problem 13: Intersection of Two Arrays
// Company: Meta, Amazon, Google
// ============================================================================
TEST(Problem13_Intersection, BasicCase) {
  auto result = intersection({1, 2, 2, 1}, {2, 2});
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0], 2);
}

TEST(Problem13_Intersection, MultipleCommon) {
  auto result = intersection({4, 9, 5}, {9, 4, 9, 8, 4});
  std::sort(result.begin(), result.end());
  EXPECT_TRUE(result == std::vector<int>({4, 9}) || 
              result == std::vector<int>({9, 4}));
}

// ============================================================================
// Problem 14: Move Zeroes
// Company: Amazon, Microsoft, Meta
// ============================================================================
TEST(Problem14_MoveZeroes, BasicCase) {
  std::vector<int> nums = {0, 1, 0, 3, 12};
  moveZeroes(nums);
  EXPECT_EQ(nums, std::vector<int>({1, 3, 12, 0, 0}));
}

TEST(Problem14_MoveZeroes, NoZeroes) {
  std::vector<int> nums = {1, 2, 3};
  moveZeroes(nums);
  EXPECT_EQ(nums, std::vector<int>({1, 2, 3}));
}

// ============================================================================
// Problem 15: Fizz Buzz
// Company: Apple, Adobe, Amazon
// ============================================================================
TEST(Problem15_FizzBuzz, BasicCase) {
  auto result = fizzBuzz(15);
  EXPECT_EQ(result[0], "1");
  EXPECT_EQ(result[2], "Fizz");
  EXPECT_EQ(result[4], "Buzz");
  EXPECT_EQ(result[14], "FizzBuzz");
}

TEST(Problem15_FizzBuzz, SmallCase) {
  auto result = fizzBuzz(5);
  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(result[4], "Buzz");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
