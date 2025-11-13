#pragma once
#include <vector>
#include <string>
#include <unordered_map>

// Problem 1: Two Sum
std::vector<int> twoSum(const std::vector<int>& nums, int target);

// Problem 2: Valid Parentheses
bool isValidParentheses(const std::string& s);

// Problem 3: Merge Two Sorted Lists
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);

// Problem 4: Best Time to Buy and Sell Stock
int maxProfit(const std::vector<int>& prices);

// Problem 5: Valid Palindrome
bool isPalindrome(const std::string& s);

// Problem 6: Maximum Subarray (Kadane's Algorithm)
int maxSubArray(const std::vector<int>& nums);

// Problem 7: Contains Duplicate
bool containsDuplicate(const std::vector<int>& nums);

// Problem 8: Reverse Linked List
ListNode* reverseList(ListNode* head);

// Problem 9: Binary Search
int binarySearch(const std::vector<int>& nums, int target);

// Problem 10: Climbing Stairs
int climbStairs(int n);

// Problem 11: Symmetric Tree
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
bool isSymmetric(TreeNode* root);

// Problem 12: Single Number
int singleNumber(const std::vector<int>& nums);

// Problem 13: Intersection of Two Arrays
std::vector<int> intersection(const std::vector<int>& nums1, const std::vector<int>& nums2);

// Problem 14: Move Zeroes
void moveZeroes(std::vector<int>& nums);

// Problem 15: Fizz Buzz
std::vector<std::string> fizzBuzz(int n);
