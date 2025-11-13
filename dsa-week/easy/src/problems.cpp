#include "../include/problems.h"
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <climits>

// ============================================================================
// Problem 1: Two Sum
// Time: O(n), Space: O(n)
// Hint: Use hash map to store complements
// ============================================================================
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
  std::unordered_map<int, int> seen;
  for (int i = 0; i < nums.size(); ++i) {
    int complement = target - nums[i];
    if (seen.count(complement)) {
      return {seen[complement], i};
    }
    seen[nums[i]] = i;
  }
  return {};
}

// ============================================================================
// Problem 2: Valid Parentheses
// Time: O(n), Space: O(n)
// Hint: Use stack to match opening and closing brackets
// ============================================================================
bool isValidParentheses(const std::string& s) {
  std::stack<char> st;
  for (char c : s) {
    if (c == '(' || c == '[' || c == '{') {
      st.push(c);
    } else {
      if (st.empty()) return false;
      char top = st.top();
      if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{')) {
        st.pop();
      } else {
        return false;
      }
    }
  }
  return st.empty();
}

// ============================================================================
// Problem 3: Merge Two Sorted Lists
// Time: O(n+m), Space: O(1)
// Hint: Use dummy node and two pointers
// ============================================================================
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  ListNode dummy(0);
  ListNode* tail = &dummy;
  while (l1 && l2) {
    if (l1->val <= l2->val) {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }
  tail->next = l1 ? l1 : l2;
  return dummy.next;
}

// ============================================================================
// Problem 4: Best Time to Buy and Sell Stock
// Time: O(n), Space: O(1)
// Hint: Track minimum price and maximum profit
// ============================================================================
int maxProfit(const std::vector<int>& prices) {
  int min_price = INT_MAX, max_profit = 0;
  for (int price : prices) {
    min_price = std::min(min_price, price);
    max_profit = std::max(max_profit, price - min_price);
  }
  return max_profit;
}

// ============================================================================
// Problem 5: Valid Palindrome
// Time: O(n), Space: O(1)
// Hint: Two pointers from both ends, skip non-alphanumeric
// ============================================================================
bool isPalindrome(const std::string& s) {
  int left = 0, right = s.size() - 1;
  while (left < right) {
    while (left < right && !std::isalnum(s[left])) ++left;
    while (left < right && !std::isalnum(s[right])) --right;
    if (std::tolower(s[left]) != std::tolower(s[right])) return false;
    ++left; --right;
  }
  return true;
}

// ============================================================================
// Problem 6: Maximum Subarray (Kadane's Algorithm)
// Time: O(n), Space: O(1)
// Hint: Track current sum and maximum sum
// ============================================================================
int maxSubArray(const std::vector<int>& nums) {
  int current_sum = nums[0], max_sum = nums[0];
  for (int i = 1; i < nums.size(); ++i) {
    current_sum = std::max(nums[i], current_sum + nums[i]);
    max_sum = std::max(max_sum, current_sum);
  }
  return max_sum;
}

// ============================================================================
// Problem 7: Contains Duplicate
// Time: O(n), Space: O(n)
// Hint: Use hash set
// ============================================================================
bool containsDuplicate(const std::vector<int>& nums) {
  std::unordered_set<int> seen;
  for (int num : nums) {
    if (seen.count(num)) return true;
    seen.insert(num);
  }
  return false;
}

// ============================================================================
// Problem 8: Reverse Linked List
// Time: O(n), Space: O(1)
// Hint: Three pointers - prev, current, next
// ============================================================================
ListNode* reverseList(ListNode* head) {
  ListNode* prev = nullptr;
  while (head) {
    ListNode* next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  return prev;
}

// ============================================================================
// Problem 9: Binary Search
// Time: O(log n), Space: O(1)
// Hint: Standard binary search
// ============================================================================
int binarySearch(const std::vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

// ============================================================================
// Problem 10: Climbing Stairs (Fibonacci)
// Time: O(n), Space: O(1)
// Hint: It's Fibonacci! ways(n) = ways(n-1) + ways(n-2)
// ============================================================================
int climbStairs(int n) {
  if (n <= 2) return n;
  int prev2 = 1, prev1 = 2;
  for (int i = 3; i <= n; ++i) {
    int curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
  }
  return prev1;
}

// ============================================================================
// Problem 11: Symmetric Tree
// Time: O(n), Space: O(h)
// Hint: Recursive helper to compare left and right subtrees
// ============================================================================
bool isSymmetric(TreeNode* root) {
  auto isMirror = [](TreeNode* left, TreeNode* right, auto& ref) -> bool {
    if (!left && !right) return true;
    if (!left || !right) return false;
    return left->val == right->val && ref(left->left, right->right, ref) && ref(left->right, right->left, ref);
  };
  return !root || isMirror(root->left, root->right, isMirror);
}

// ============================================================================
// Problem 12: Single Number
// Time: O(n), Space: O(1)
// Hint: XOR! a ^ a = 0, a ^ 0 = a
// ============================================================================
int singleNumber(const std::vector<int>& nums) {
  int result = 0;
  for (int num : nums) result ^= num;
  return result;
}

// ============================================================================
// Problem 13: Intersection of Two Arrays
// Time: O(n+m), Space: O(min(n,m))
// Hint: Use two hash sets
// ============================================================================
std::vector<int> intersection(const std::vector<int>& nums1, const std::vector<int>& nums2) {
  std::unordered_set<int> set1(nums1.begin(), nums1.end());
  std::unordered_set<int> result_set;
  for (int num : nums2) {
    if (set1.count(num)) result_set.insert(num);
  }
  return std::vector<int>(result_set.begin(), result_set.end());
}

// ============================================================================
// Problem 14: Move Zeroes
// Time: O(n), Space: O(1)
// Hint: Two pointers - one for non-zero position
// ============================================================================
void moveZeroes(std::vector<int>& nums) {
  int pos = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (nums[i] != 0) nums[pos++] = nums[i];
  }
  while (pos < nums.size()) nums[pos++] = 0;
}

// ============================================================================
// Problem 15: Fizz Buzz
// Time: O(n), Space: O(n)
// Hint: Check divisibility by 3 and 5
// ============================================================================
std::vector<std::string> fizzBuzz(int n) {
  std::vector<std::string> result;
  for (int i = 1; i <= n; ++i) {
    if (i % 15 == 0) result.push_back("FizzBuzz");
    else if (i % 3 == 0) result.push_back("Fizz");
    else if (i % 5 == 0) result.push_back("Buzz");
    else result.push_back(std::to_string(i));
  }
  return result;
}
