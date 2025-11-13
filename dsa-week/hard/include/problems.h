#pragma once
#include <vector>
#include <string>

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

// 41. Median of Two Sorted Arrays - O(log(min(m,n)))
double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2);

// 42. Trapping Rain Water - O(n)
int trap(const std::vector<int>& height);

// 43. Longest Valid Parentheses - O(n)
int longestValidParentheses(const std::string& s);

// 44. Wildcard Matching - O(m*n)
bool isMatch(const std::string& s, const std::string& p);

// 45. Edit Distance - O(m*n)
int minDistance(const std::string& word1, const std::string& word2);

// 46. Merge K Sorted Lists - O(n log k)
ListNode* mergeKLists(std::vector<ListNode*>& lists);

// 47. Largest Rectangle in Histogram - O(n)
int largestRectangleArea(const std::vector<int>& heights);

// 48. Maximal Rectangle - O(m*n)
int maximalRectangle(std::vector<std::vector<char>>& matrix);

// 49. Word Ladder - O(m²*n)
int ladderLength(const std::string& beginWord, const std::string& endWord, std::vector<std::string>& wordList);

// 50. Serialize and Deserialize Binary Tree - O(n)
class Codec {
public:
  std::string serialize(TreeNode* root);
  TreeNode* deserialize(const std::string& data);
};
