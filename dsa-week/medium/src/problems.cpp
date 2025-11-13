#include "../include/problems.h"
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <climits>

// 16. Three Sum - Sort + Two Pointers
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
  std::vector<std::vector<int>> result;
  std::sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); ++i) {
    if (i > 0 && nums[i] == nums[i-1]) continue;
    int left = i + 1, right = nums.size() - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum == 0) {
        result.push_back({nums[i], nums[left], nums[right]});
        while (left < right && nums[left] == nums[left+1]) ++left;
        while (left < right && nums[right] == nums[right-1]) --right;
        ++left; --right;
      } else if (sum < 0) ++left;
      else --right;
    }
  }
  return result;
}

// 17. Group Anagrams - Hash by sorted string
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
  std::unordered_map<std::string, std::vector<std::string>> groups;
  for (const auto& s : strs) {
    std::string key = s;
    std::sort(key.begin(), key.end());
    groups[key].push_back(s);
  }
  std::vector<std::vector<std::string>> result;
  for (auto& [_, group] : groups) result.push_back(std::move(group));
  return result;
}

// 18. Longest Substring Without Repeating - Sliding Window
int lengthOfLongestSubstring(const std::string& s) {
  std::unordered_map<char, int> last_seen;
  int max_len = 0, start = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (last_seen.count(s[i]) && last_seen[s[i]] >= start) {
      start = last_seen[s[i]] + 1;
    }
    last_seen[s[i]] = i;
    max_len = std::max(max_len, i - start + 1);
  }
  return max_len;
}

// 19. Container With Most Water - Two Pointers
int maxArea(const std::vector<int>& height) {
  int left = 0, right = height.size() - 1, max_area = 0;
  while (left < right) {
    max_area = std::max(max_area, std::min(height[left], height[right]) * (right - left));
    if (height[left] < height[right]) ++left;
    else --right;
  }
  return max_area;
}

// 20. Product of Array Except Self - Prefix/Suffix
std::vector<int> productExceptSelf(const std::vector<int>& nums) {
  int n = nums.size();
  std::vector<int> result(n, 1);
  for (int i = 1; i < n; ++i) result[i] = result[i-1] * nums[i-1];
  int suffix = 1;
  for (int i = n - 1; i >= 0; --i) {
    result[i] *= suffix;
    suffix *= nums[i];
  }
  return result;
}

// 21. Rotate Image - Transpose + Reverse
void rotate(std::vector<std::vector<int>>& matrix) {
  int n = matrix.size();
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      std::swap(matrix[i][j], matrix[j][i]);
  for (auto& row : matrix) std::reverse(row.begin(), row.end());
}

// 22. Spiral Matrix - Layer by Layer
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
  std::vector<int> result;
  if (matrix.empty()) return result;
  int top = 0, bottom = matrix.size() - 1, left = 0, right = matrix[0].size() - 1;
  while (top <= bottom && left <= right) {
    for (int i = left; i <= right; ++i) result.push_back(matrix[top][i]);
    ++top;
    for (int i = top; i <= bottom; ++i) result.push_back(matrix[i][right]);
    --right;
    if (top <= bottom) {
      for (int i = right; i >= left; --i) result.push_back(matrix[bottom][i]);
      --bottom;
    }
    if (left <= right) {
      for (int i = bottom; i >= top; --i) result.push_back(matrix[i][left]);
      ++left;
    }
  }
  return result;
}

// 23. Jump Game - Greedy
bool canJump(const std::vector<int>& nums) {
  int max_reach = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (i > max_reach) return false;
    max_reach = std::max(max_reach, i + nums[i]);
  }
  return true;
}

// 24. Merge Intervals - Sort + Merge
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
  if (intervals.empty()) return {};
  std::sort(intervals.begin(), intervals.end());
  std::vector<std::vector<int>> result = {intervals[0]};
  for (int i = 1; i < intervals.size(); ++i) {
    if (intervals[i][0] <= result.back()[1]) {
      result.back()[1] = std::max(result.back()[1], intervals[i][1]);
    } else {
      result.push_back(intervals[i]);
    }
  }
  return result;
}

// 25. Unique Paths - DP
int uniquePaths(int m, int n) {
  std::vector<int> dp(n, 1);
  for (int i = 1; i < m; ++i)
    for (int j = 1; j < n; ++j)
      dp[j] += dp[j-1];
  return dp[n-1];
}

// 26. Coin Change - DP
int coinChange(const std::vector<int>& coins, int amount) {
  std::vector<int> dp(amount + 1, amount + 1);
  dp[0] = 0;
  for (int i = 1; i <= amount; ++i)
    for (int coin : coins)
      if (coin <= i) dp[i] = std::min(dp[i], dp[i - coin] + 1);
  return dp[amount] > amount ? -1 : dp[amount];
}

// 27. Longest Increasing Subsequence - Binary Search
int lengthOfLIS(const std::vector<int>& nums) {
  std::vector<int> tails;
  for (int num : nums) {
    auto it = std::lower_bound(tails.begin(), tails.end(), num);
    if (it == tails.end()) tails.push_back(num);
    else *it = num;
  }
  return tails.size();
}

// 28. Word Break - DP
bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict) {
  std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
  std::vector<bool> dp(s.size() + 1);
  dp[0] = true;
  for (int i = 1; i <= s.size(); ++i)
    for (int j = 0; j < i; ++j)
      if (dp[j] && dict.count(s.substr(j, i - j))) {
        dp[i] = true;
        break;
      }
  return dp[s.size()];
}

// 29. House Robber II - DP with circular constraint
int rob(const std::vector<int>& nums) {
  if (nums.size() == 1) return nums[0];
  auto robLinear = [](const std::vector<int>& nums, int start, int end) {
    int prev2 = 0, prev1 = 0;
    for (int i = start; i < end; ++i) {
      int curr = std::max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = curr;
    }
    return prev1;
  };
  return std::max(robLinear(nums, 0, nums.size() - 1), robLinear(nums, 1, nums.size()));
}

// 30. Number of Islands - DFS
int numIslands(std::vector<std::vector<char>>& grid) {
  int count = 0;
  auto dfs = [&](int i, int j, auto& ref) -> void {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != '1') return;
    grid[i][j] = '0';
    ref(i+1, j, ref); ref(i-1, j, ref); ref(i, j+1, ref); ref(i, j-1, ref);
  };
  for (int i = 0; i < grid.size(); ++i)
    for (int j = 0; j < grid[0].size(); ++j)
      if (grid[i][j] == '1') { ++count; dfs(i, j, dfs); }
  return count;
}

// 31. Course Schedule - Topological Sort (DFS)
bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
  std::vector<std::vector<int>> graph(numCourses);
  for (const auto& p : prerequisites) graph[p[1]].push_back(p[0]);
  std::vector<int> state(numCourses, 0); // 0=unvisited, 1=visiting, 2=visited
  auto hasCycle = [&](int node, auto& ref) -> bool {
    if (state[node] == 1) return true;
    if (state[node] == 2) return false;
    state[node] = 1;
    for (int next : graph[node]) if (ref(next, ref)) return true;
    state[node] = 2;
    return false;
  };
  for (int i = 0; i < numCourses; ++i)
    if (hasCycle(i, hasCycle)) return false;
  return true;
}

// 32. Implement Trie
Trie::Trie() : root_(new Node()) {}

void Trie::insert(const std::string& word) {
  Node* curr = root_;
  for (char c : word) {
    if (!curr->children[c]) curr->children[c] = new Node();
    curr = curr->children[c];
  }
  curr->is_end = true;
}

bool Trie::search(const std::string& word) {
  Node* curr = root_;
  for (char c : word) {
    if (!curr->children[c]) return false;
    curr = curr->children[c];
  }
  return curr->is_end;
}

bool Trie::startsWith(const std::string& prefix) {
  Node* curr = root_;
  for (char c : prefix) {
    if (!curr->children[c]) return false;
    curr = curr->children[c];
  }
  return true;
}

// 33. Kth Largest Element - Quickselect
int findKthLargest(std::vector<int>& nums, int k) {
  std::nth_element(nums.begin(), nums.begin() + nums.size() - k, nums.end());
  return nums[nums.size() - k];
}

// 34. Top K Frequent Elements - Bucket Sort
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
  std::unordered_map<int, int> freq;
  for (int num : nums) ++freq[num];
  std::vector<std::vector<int>> buckets(nums.size() + 1);
  for (const auto& [num, count] : freq) buckets[count].push_back(num);
  std::vector<int> result;
  for (int i = buckets.size() - 1; i >= 0 && result.size() < k; --i)
    for (int num : buckets[i]) {
      result.push_back(num);
      if (result.size() == k) return result;
    }
  return result;
}

// 35. Find Peak Element - Binary Search
int findPeakElement(const std::vector<int>& nums) {
  int left = 0, right = nums.size() - 1;
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] > nums[mid + 1]) right = mid;
    else left = mid + 1;
  }
  return left;
}

// 36. Search in Rotated Sorted Array - Modified Binary Search
int search(const std::vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[left] <= nums[mid]) {
      if (nums[left] <= target && target < nums[mid]) right = mid - 1;
      else left = mid + 1;
    } else {
      if (nums[mid] < target && target <= nums[right]) left = mid + 1;
      else right = mid - 1;
    }
  }
  return -1;
}

// 37. Binary Tree Level Order Traversal - BFS
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
  if (!root) return {};
  std::vector<std::vector<int>> result;
  std::queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int size = q.size();
    std::vector<int> level;
    for (int i = 0; i < size; ++i) {
      TreeNode* node = q.front(); q.pop();
      level.push_back(node->val);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
    result.push_back(level);
  }
  return result;
}

// 38. Validate BST - Inorder or Range Check
bool isValidBST(TreeNode* root) {
  auto validate = [](TreeNode* node, long min_val, long max_val, auto& ref) -> bool {
    if (!node) return true;
    if (node->val <= min_val || node->val >= max_val) return false;
    return ref(node->left, min_val, node->val, ref) && ref(node->right, node->val, max_val, ref);
  };
  return validate(root, LONG_MIN, LONG_MAX, validate);
}

// 39. Lowest Common Ancestor - Recursive
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (!root || root == p || root == q) return root;
  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);
  return left && right ? root : (left ? left : right);
}

// 40. Construct Binary Tree - Recursive with index map
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
  std::unordered_map<int, int> idx;
  for (int i = 0; i < inorder.size(); ++i) idx[inorder[i]] = i;
  int pre_idx = 0;
  auto build = [&](int left, int right, auto& ref) -> TreeNode* {
    if (left > right) return nullptr;
    TreeNode* root = new TreeNode(preorder[pre_idx++]);
    int mid = idx[root->val];
    root->left = ref(left, mid - 1, ref);
    root->right = ref(mid + 1, right, ref);
    return root;
  };
  return build(0, inorder.size() - 1, build);
}
