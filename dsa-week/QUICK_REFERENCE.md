# DSA Week - Quick Reference Guide

## 🚀 Build & Test Commands

```bash
# Initial setup
cd cpp-mastery/dsa-week
mkdir build && cd build
cmake ..

# Build all
make -j4

# Test by difficulty
./test_easy_problems      # 35 tests
./test_medium_problems    # 25 tests
./test_hard_problems      # 10 tests

# Run all tests
ctest

# Test specific problem
./test_easy_problems --gtest_filter="*TwoSum*"
./test_medium_problems --gtest_filter="*ThreeSum*"
```

---

## 📚 Problem Index

### Easy (1-15)
| # | Problem | Pattern | Complexity |
|---|---------|---------|------------|
| 1 | Two Sum | Hash Map | O(n) / O(n) |
| 2 | Valid Parentheses | Stack | O(n) / O(n) |
| 3 | Merge Two Sorted Lists | Two Pointers | O(n+m) / O(1) |
| 4 | Best Time to Buy/Sell Stock | Greedy | O(n) / O(1) |
| 5 | Valid Palindrome | Two Pointers | O(n) / O(1) |
| 6 | Maximum Subarray | Kadane's | O(n) / O(1) |
| 7 | Contains Duplicate | Hash Set | O(n) / O(n) |
| 8 | Reverse Linked List | Iterative | O(n) / O(1) |
| 9 | Binary Search | Binary Search | O(log n) / O(1) |
| 10 | Climbing Stairs | DP/Fibonacci | O(n) / O(1) |
| 11 | Symmetric Tree | Recursion | O(n) / O(h) |
| 12 | Single Number | XOR | O(n) / O(1) |
| 13 | Intersection of Arrays | Hash Set | O(n+m) / O(n) |
| 14 | Move Zeroes | Two Pointers | O(n) / O(1) |
| 15 | Fizz Buzz | Iteration | O(n) / O(n) |

### Medium (16-40)
| # | Problem | Pattern | Complexity |
|---|---------|---------|------------|
| 16 | Three Sum | Sort + Two Pointers | O(n²) / O(1) |
| 17 | Group Anagrams | Hash Map | O(n*k log k) / O(n*k) |
| 18 | Longest Substring | Sliding Window | O(n) / O(k) |
| 19 | Container With Most Water | Two Pointers | O(n) / O(1) |
| 20 | Product Except Self | Prefix/Suffix | O(n) / O(1) |
| 21 | Rotate Image | Matrix | O(n²) / O(1) |
| 22 | Spiral Matrix | Simulation | O(m*n) / O(1) |
| 23 | Jump Game | Greedy | O(n) / O(1) |
| 24 | Merge Intervals | Sort + Merge | O(n log n) / O(n) |
| 25 | Unique Paths | DP | O(m*n) / O(n) |
| 26 | Coin Change | DP | O(n*amount) / O(amount) |
| 27 | Longest Increasing Subsequence | Binary Search | O(n log n) / O(n) |
| 28 | Word Break | DP | O(n²) / O(n) |
| 29 | House Robber II | DP | O(n) / O(1) |
| 30 | Number of Islands | DFS | O(m*n) / O(m*n) |
| 31 | Course Schedule | Topological Sort | O(V+E) / O(V+E) |
| 32 | Implement Trie | Trie | O(m) / O(n*m) |
| 33 | Kth Largest Element | Quickselect | O(n) avg / O(1) |
| 34 | Top K Frequent | Bucket Sort | O(n) / O(n) |
| 35 | Find Peak Element | Binary Search | O(log n) / O(1) |
| 36 | Search Rotated Array | Binary Search | O(log n) / O(1) |
| 37 | Level Order Traversal | BFS | O(n) / O(n) |
| 38 | Validate BST | DFS | O(n) / O(h) |
| 39 | Lowest Common Ancestor | Recursion | O(n) / O(h) |
| 40 | Build Tree | Recursion | O(n) / O(n) |

### Hard (41-50)
| # | Problem | Pattern | Complexity |
|---|---------|---------|------------|
| 41 | Median of Two Sorted Arrays | Binary Search | O(log(min(m,n))) / O(1) |
| 42 | Trapping Rain Water | Two Pointers | O(n) / O(1) |
| 43 | Longest Valid Parentheses | Stack | O(n) / O(n) |
| 44 | Wildcard Matching | DP | O(m*n) / O(m*n) |
| 45 | Edit Distance | DP | O(m*n) / O(m*n) |
| 46 | Merge K Sorted Lists | Min Heap | O(n log k) / O(k) |
| 47 | Largest Rectangle | Stack | O(n) / O(n) |
| 48 | Maximal Rectangle | Stack + DP | O(m*n) / O(n) |
| 49 | Word Ladder | BFS | O(m²*n) / O(m*n) |
| 50 | Serialize/Deserialize Tree | DFS | O(n) / O(n) |

---

## 🔑 Pattern Cheat Sheet

### Hash Map/Set
- Two Sum, Contains Duplicate, Group Anagrams
- **When:** Need O(1) lookup, frequency counting
- **Space:** O(n)

### Two Pointers
- Three Sum, Container With Water, Trapping Rain Water
- **When:** Sorted array, find pairs/triplets
- **Space:** O(1)

### Sliding Window
- Longest Substring, Max Subarray
- **When:** Contiguous subarray/substring
- **Space:** O(k) where k is window size

### Stack
- Valid Parentheses, Largest Rectangle
- **When:** Matching, monotonic sequences
- **Space:** O(n)

### Binary Search
- Search Rotated Array, Find Peak, Median of Arrays
- **When:** Sorted/rotated array, search space reduction
- **Space:** O(1)

### Dynamic Programming
- Coin Change, LIS, Edit Distance, Word Break
- **When:** Optimal substructure, overlapping subproblems
- **Space:** O(n) to O(n²)

### DFS/BFS
- Number of Islands, Course Schedule, Word Ladder
- **When:** Graph/tree traversal, shortest path
- **Space:** O(V+E)

### Heap
- Kth Largest, Top K Frequent, Merge K Lists
- **When:** K largest/smallest, priority queue
- **Space:** O(k)

---

## 💡 Common Tricks

### XOR for Single Number
```cpp
int result = 0;
for (int num : nums) result ^= num;
// a ^ a = 0, a ^ 0 = a
```

### Kadane's Algorithm
```cpp
int current = nums[0], max_sum = nums[0];
for (int i = 1; i < n; ++i) {
  current = max(nums[i], current + nums[i]);
  max_sum = max(max_sum, current);
}
```

### Two Pointers for Sorted Array
```cpp
int left = 0, right = n - 1;
while (left < right) {
  int sum = nums[left] + nums[right];
  if (sum == target) return {left, right};
  else if (sum < target) ++left;
  else --right;
}
```

### Sliding Window
```cpp
unordered_map<char, int> window;
int left = 0, max_len = 0;
for (int right = 0; right < s.size(); ++right) {
  window[s[right]]++;
  while (/* condition violated */) {
    window[s[left]]--;
    ++left;
  }
  max_len = max(max_len, right - left + 1);
}
```

### Binary Search Template
```cpp
int left = 0, right = n - 1;
while (left <= right) {
  int mid = left + (right - left) / 2;
  if (nums[mid] == target) return mid;
  else if (nums[mid] < target) left = mid + 1;
  else right = mid - 1;
}
return -1;
```

---

## 🎯 Interview Tips

1. **Clarify Requirements**
   - Input constraints (size, range, duplicates)
   - Output format
   - Edge cases

2. **Think Out Loud**
   - Explain your approach
   - Discuss trade-offs
   - Mention alternatives

3. **Start Simple**
   - Brute force first
   - Then optimize
   - Explain complexity

4. **Test Your Code**
   - Walk through example
   - Check edge cases
   - Verify complexity

5. **Common Edge Cases**
   - Empty input
   - Single element
   - All same elements
   - Negative numbers
   - Integer overflow

---

## 📊 Complexity Quick Reference

| Notation | Name | Example |
|----------|------|---------|
| O(1) | Constant | Hash map lookup |
| O(log n) | Logarithmic | Binary search |
| O(n) | Linear | Single pass |
| O(n log n) | Linearithmic | Merge sort |
| O(n²) | Quadratic | Nested loops |
| O(2ⁿ) | Exponential | Recursive fibonacci |

---

## 🏆 Progress Tracking

- [ ] Easy 1-5 (Foundation)
- [ ] Easy 6-10 (Core patterns)
- [ ] Easy 11-15 (Advanced basics)
- [ ] Medium 16-20 (Two pointers + arrays)
- [ ] Medium 21-25 (Matrix + DP intro)
- [ ] Medium 26-30 (DP + graphs)
- [ ] Medium 31-35 (Advanced DS)
- [ ] Medium 36-40 (Trees)
- [ ] Hard 41-45 (Advanced algorithms)
- [ ] Hard 46-50 (Complex problems)

---

## 📖 Resources

- **Documentation:** See PROBLEMS_DETAILED.md
- **Completion Guide:** See ALL_COMPLETE.md
- **Easy Solutions:** See EASY_COMPLETE.md
- **Main README:** See README.md
