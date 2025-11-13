#pragma once
#include <vector>
#include <string>
#include <unordered_map>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 16. Three Sum - O(n²)
std::vector<std::vector<int>> threeSum(std::vector<int>& nums);

// 17. Group Anagrams - O(n*k)
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);

// 18. Longest Substring Without Repeating - O(n)
int lengthOfLongestSubstring(const std::string& s);

// 19. Container With Most Water - O(n)
int maxArea(const std::vector<int>& height);

// 20. Product of Array Except Self - O(n)
std::vector<int> productExceptSelf(const std::vector<int>& nums);

// 21. Rotate Image - O(n²)
void rotate(std::vector<std::vector<int>>& matrix);

// 22. Spiral Matrix - O(m*n)
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix);

// 23. Jump Game - O(n)
bool canJump(const std::vector<int>& nums);

// 24. Merge Intervals - O(n log n)
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals);

// 25. Unique Paths - O(m*n)
int uniquePaths(int m, int n);

// 26. Coin Change - O(n*amount)
int coinChange(const std::vector<int>& coins, int amount);

// 27. Longest Increasing Subsequence - O(n log n)
int lengthOfLIS(const std::vector<int>& nums);

// 28. Word Break - O(n²)
bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict);

// 29. House Robber II - O(n)
int rob(const std::vector<int>& nums);

// 30. Number of Islands - O(m*n)
int numIslands(std::vector<std::vector<char>>& grid);

// 31. Course Schedule - O(V+E)
bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites);

// 32. Implement Trie - O(m) per operation
class Trie {
public:
  Trie();
  void insert(const std::string& word);
  bool search(const std::string& word);
  bool startsWith(const std::string& prefix);
private:
  struct Node {
    std::unordered_map<char, Node*> children;
    bool is_end = false;
  };
  Node* root_;
};

// 33. Kth Largest Element - O(n) average
int findKthLargest(std::vector<int>& nums, int k);

// 34. Top K Frequent Elements - O(n)
std::vector<int> topKFrequent(const std::vector<int>& nums, int k);

// 35. Find Peak Element - O(log n)
int findPeakElement(const std::vector<int>& nums);

// 36. Search in Rotated Sorted Array - O(log n)
int search(const std::vector<int>& nums, int target);

// 37. Binary Tree Level Order Traversal - O(n)
std::vector<std::vector<int>> levelOrder(TreeNode* root);

// 38. Validate BST - O(n)
bool isValidBST(TreeNode* root);

// 39. Lowest Common Ancestor - O(n)
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);

// 40. Construct Binary Tree from Preorder and Inorder - O(n)
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);
