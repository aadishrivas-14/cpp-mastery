#include "../include/problems.h"
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <climits>

// 41. Median of Two Sorted Arrays - Binary Search
double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
  if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
  int m = nums1.size(), n = nums2.size();
  int left = 0, right = m;
  while (left <= right) {
    int i = (left + right) / 2;
    int j = (m + n + 1) / 2 - i;
    int maxLeft1 = (i == 0) ? INT_MIN : nums1[i-1];
    int minRight1 = (i == m) ? INT_MAX : nums1[i];
    int maxLeft2 = (j == 0) ? INT_MIN : nums2[j-1];
    int minRight2 = (j == n) ? INT_MAX : nums2[j];
    if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
      if ((m + n) % 2 == 0) return (std::max(maxLeft1, maxLeft2) + std::min(minRight1, minRight2)) / 2.0;
      return std::max(maxLeft1, maxLeft2);
    } else if (maxLeft1 > minRight2) right = i - 1;
    else left = i + 1;
  }
  return 0.0;
}

// 42. Trapping Rain Water - Two Pointers
int trap(const std::vector<int>& height) {
  int left = 0, right = height.size() - 1;
  int left_max = 0, right_max = 0, water = 0;
  while (left < right) {
    if (height[left] < height[right]) {
      if (height[left] >= left_max) left_max = height[left];
      else water += left_max - height[left];
      ++left;
    } else {
      if (height[right] >= right_max) right_max = height[right];
      else water += right_max - height[right];
      --right;
    }
  }
  return water;
}

// 43. Longest Valid Parentheses - Stack
int longestValidParentheses(const std::string& s) {
  std::stack<int> st;
  st.push(-1);
  int max_len = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '(') st.push(i);
    else {
      st.pop();
      if (st.empty()) st.push(i);
      else max_len = std::max(max_len, i - st.top());
    }
  }
  return max_len;
}

// 44. Wildcard Matching - DP
bool isMatch(const std::string& s, const std::string& p) {
  int m = s.size(), n = p.size();
  std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1));
  dp[0][0] = true;
  for (int j = 1; j <= n; ++j) if (p[j-1] == '*') dp[0][j] = dp[0][j-1];
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (p[j-1] == '*') dp[i][j] = dp[i-1][j] || dp[i][j-1];
      else if (p[j-1] == '?' || s[i-1] == p[j-1]) dp[i][j] = dp[i-1][j-1];
    }
  }
  return dp[m][n];
}

// 45. Edit Distance - DP
int minDistance(const std::string& word1, const std::string& word2) {
  int m = word1.size(), n = word2.size();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
  for (int i = 0; i <= m; ++i) dp[i][0] = i;
  for (int j = 0; j <= n; ++j) dp[0][j] = j;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
      else dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    }
  }
  return dp[m][n];
}

// 46. Merge K Sorted Lists - Min Heap
ListNode* mergeKLists(std::vector<ListNode*>& lists) {
  auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
  std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pq(cmp);
  for (auto list : lists) if (list) pq.push(list);
  ListNode dummy(0);
  ListNode* tail = &dummy;
  while (!pq.empty()) {
    ListNode* node = pq.top(); pq.pop();
    tail->next = node;
    tail = tail->next;
    if (node->next) pq.push(node->next);
  }
  return dummy.next;
}

// 47. Largest Rectangle in Histogram - Stack
int largestRectangleArea(const std::vector<int>& heights) {
  std::stack<int> st;
  int max_area = 0;
  for (int i = 0; i <= heights.size(); ++i) {
    int h = (i == heights.size()) ? 0 : heights[i];
    while (!st.empty() && heights[st.top()] > h) {
      int height = heights[st.top()]; st.pop();
      int width = st.empty() ? i : i - st.top() - 1;
      max_area = std::max(max_area, height * width);
    }
    st.push(i);
  }
  return max_area;
}

// 48. Maximal Rectangle - Use Histogram
int maximalRectangle(std::vector<std::vector<char>>& matrix) {
  if (matrix.empty()) return 0;
  int m = matrix.size(), n = matrix[0].size();
  std::vector<int> heights(n);
  int max_area = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
    }
    max_area = std::max(max_area, largestRectangleArea(heights));
  }
  return max_area;
}

// 49. Word Ladder - BFS
int ladderLength(const std::string& beginWord, const std::string& endWord, std::vector<std::string>& wordList) {
  std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
  if (!dict.count(endWord)) return 0;
  std::queue<std::string> q;
  q.push(beginWord);
  int level = 1;
  while (!q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      std::string word = q.front(); q.pop();
      if (word == endWord) return level;
      for (int j = 0; j < word.size(); ++j) {
        char orig = word[j];
        for (char c = 'a'; c <= 'z'; ++c) {
          word[j] = c;
          if (dict.count(word)) {
            q.push(word);
            dict.erase(word);
          }
        }
        word[j] = orig;
      }
    }
    ++level;
  }
  return 0;
}

// 50. Serialize and Deserialize Binary Tree
std::string Codec::serialize(TreeNode* root) {
  if (!root) return "#";
  return std::to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
}

TreeNode* Codec::deserialize(const std::string& data) {
  std::istringstream iss(data);
  std::string val;
  auto build = [&](auto& ref) -> TreeNode* {
    if (!std::getline(iss, val, ',') || val == "#") return nullptr;
    TreeNode* node = new TreeNode(std::stoi(val));
    node->left = ref(ref);
    node->right = ref(ref);
    return node;
  };
  return build(build);
}
