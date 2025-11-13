# DSA Week - Detailed Problem Descriptions

## Easy Problems (15)

### 1. Two Sum
**Company:** Amazon, Google, Meta  
**Difficulty:** Easy  
**Topics:** Array, Hash Table

**Problem:** Given an array of integers and a target, return indices of two numbers that add up to target.

**Example:**
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9
```

**Constraints:**
- 2 <= nums.length <= 10^4
- Each input has exactly one solution

**Hints:**
- Use hash map to store complements
- Time: O(n), Space: O(n)

---

### 2. Valid Parentheses
**Company:** Microsoft, Meta, Amazon  
**Difficulty:** Easy  
**Topics:** Stack, String

**Problem:** Determine if string of brackets is valid (properly closed and nested).

**Example:**
```
Input: s = "()[]{}"
Output: true

Input: s = "([)]"
Output: false
```

**Hints:**
- Use stack for matching
- Push opening, pop and match closing

---

### 3. Merge Two Sorted Lists
**Company:** Amazon, Apple, Microsoft  
**Difficulty:** Easy  
**Topics:** Linked List, Recursion

**Problem:** Merge two sorted linked lists into one sorted list.

**Example:**
```
Input: l1 = [1,2,4], l2 = [1,3,4]
Output: [1,1,2,3,4,4]
```

**Hints:**
- Use dummy node
- Compare and link nodes

---

### 4. Best Time to Buy and Sell Stock
**Company:** Amazon, Bloomberg, Microsoft  
**Difficulty:** Easy  
**Topics:** Array, Dynamic Programming

**Problem:** Find maximum profit from one buy and one sell.

**Example:**
```
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price=1), sell on day 5 (price=6), profit = 5
```

**Hints:**
- Track minimum price seen so far
- Track maximum profit

---

### 5. Valid Palindrome
**Company:** Meta, Microsoft, Amazon  
**Difficulty:** Easy  
**Topics:** Two Pointers, String

**Problem:** Check if string is palindrome (ignoring non-alphanumeric, case-insensitive).

**Example:**
```
Input: s = "A man, a plan, a canal: Panama"
Output: true
```

**Hints:**
- Two pointers from both ends
- Skip non-alphanumeric characters

---

### 6. Maximum Subarray (Kadane's Algorithm)
**Company:** Amazon, Google, Microsoft  
**Difficulty:** Easy  
**Topics:** Array, Dynamic Programming

**Problem:** Find contiguous subarray with largest sum.

**Example:**
```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6
```

**Hints:**
- Kadane's algorithm
- current_sum = max(num, current_sum + num)

---

### 7. Contains Duplicate
**Company:** Apple, Adobe, Amazon  
**Difficulty:** Easy  
**Topics:** Array, Hash Table

**Problem:** Return true if any value appears at least twice.

**Example:**
```
Input: nums = [1,2,3,1]
Output: true
```

**Hints:**
- Use hash set to track seen numbers

---

### 8. Reverse Linked List
**Company:** Amazon, Microsoft, Meta  
**Difficulty:** Easy  
**Topics:** Linked List, Recursion

**Problem:** Reverse a singly linked list.

**Example:**
```
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
```

**Hints:**
- Three pointers: prev, current, next
- Iterative or recursive

---

### 9. Binary Search
**Company:** Google, Meta, Amazon  
**Difficulty:** Easy  
**Topics:** Array, Binary Search

**Problem:** Search for target in sorted array, return index or -1.

**Example:**
```
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
```

**Hints:**
- Standard binary search
- mid = (left + right) / 2

---

### 10. Climbing Stairs
**Company:** Amazon, Adobe, Google  
**Difficulty:** Easy  
**Topics:** Dynamic Programming, Math

**Problem:** Count ways to climb n stairs (1 or 2 steps at a time).

**Example:**
```
Input: n = 3
Output: 3
Explanation: 1+1+1, 1+2, 2+1
```

**Hints:**
- It's Fibonacci!
- ways(n) = ways(n-1) + ways(n-2)

---

### 11. Symmetric Tree
**Company:** Microsoft, Amazon, Meta  
**Difficulty:** Easy  
**Topics:** Tree, DFS, BFS

**Problem:** Check if binary tree is mirror of itself.

**Example:**
```
Input: root = [1,2,2,3,4,4,3]
Output: true
```

**Hints:**
- Recursive helper to compare subtrees
- Check if left subtree mirrors right subtree

---

### 12. Single Number
**Company:** Google, Apple, Amazon  
**Difficulty:** Easy  
**Topics:** Array, Bit Manipulation

**Problem:** Find the number that appears once (all others appear twice).

**Example:**
```
Input: nums = [2,2,1]
Output: 1
```

**Hints:**
- XOR magic: a ^ a = 0, a ^ 0 = a
- XOR all numbers

---

### 13. Intersection of Two Arrays
**Company:** Meta, Amazon, Google  
**Difficulty:** Easy  
**Topics:** Array, Hash Table

**Problem:** Return unique elements present in both arrays.

**Example:**
```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
```

**Hints:**
- Use two hash sets
- Or sort and two pointers

---

### 14. Move Zeroes
**Company:** Amazon, Microsoft, Meta  
**Difficulty:** Easy  
**Topics:** Array, Two Pointers

**Problem:** Move all zeros to end, maintain relative order of non-zeros.

**Example:**
```
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
```

**Hints:**
- Two pointers
- One tracks position for next non-zero

---

### 15. Fizz Buzz
**Company:** Apple, Adobe, Amazon  
**Difficulty:** Easy  
**Topics:** Math, String

**Problem:** Return array where:
- "Fizz" if divisible by 3
- "Buzz" if divisible by 5
- "FizzBuzz" if divisible by both
- Number as string otherwise

**Example:**
```
Input: n = 5
Output: ["1","2","Fizz","4","Buzz"]
```

**Hints:**
- Check % 15 first, then % 3, then % 5

---

## Medium Problems (25)

### 16. 3Sum
**Company:** Amazon, Meta, Google  
**Difficulty:** Medium  
**Topics:** Array, Two Pointers, Sorting

**Problem:** Find all unique triplets that sum to zero.

**Hints:**
- Sort array
- Fix one element, use two pointers for remaining two
- Time: O(n²)

---

### 17. Longest Substring Without Repeating Characters
**Company:** Amazon, Google, Meta  
**Difficulty:** Medium  
**Topics:** String, Sliding Window, Hash Table

**Problem:** Find length of longest substring without repeating characters.

**Hints:**
- Sliding window with hash set
- Expand window, shrink when duplicate found

---

### 18. Container With Most Water
**Company:** Amazon, Bloomberg, Google  
**Difficulty:** Medium  
**Topics:** Array, Two Pointers, Greedy

**Problem:** Find two lines that form container with most water.

**Hints:**
- Two pointers from both ends
- Move pointer with smaller height

---

### 19. Group Anagrams
**Company:** Amazon, Microsoft, Meta  
**Difficulty:** Medium  
**Topics:** String, Hash Table, Sorting

**Problem:** Group strings that are anagrams.

**Hints:**
- Use sorted string as key
- Or character count as key

---

### 20. Longest Palindromic Substring
**Company:** Amazon, Meta, Microsoft  
**Difficulty:** Medium  
**Topics:** String, Dynamic Programming

**Problem:** Find longest palindromic substring.

**Hints:**
- Expand around center
- Or DP: dp[i][j] = is substring from i to j palindrome

---

## Hard Problems (10)

### 41. Trapping Rain Water
**Company:** Amazon, Google, Meta  
**Difficulty:** Hard  
**Topics:** Array, Two Pointers, Stack

**Problem:** Calculate how much water can be trapped after raining.

**Hints:**
- Two pointers with left_max and right_max
- Or use stack

---

### 42. Median of Two Sorted Arrays
**Company:** Amazon, Microsoft, Google  
**Difficulty:** Hard  
**Topics:** Array, Binary Search, Divide and Conquer

**Problem:** Find median of two sorted arrays in O(log(m+n)).

**Hints:**
- Binary search on smaller array
- Partition both arrays

---

### 50. Sliding Window Maximum
**Company:** Amazon, Google, Microsoft  
**Difficulty:** Hard  
**Topics:** Array, Sliding Window, Heap, Deque

**Problem:** Find maximum in each sliding window of size k.

**Hints:**
- Use deque to maintain decreasing order
- Or use max heap with lazy deletion

---

## Study Plan

**Week Schedule:**
- Day 1-2: Easy (15 problems)
- Day 3-5: Medium (25 problems)
- Day 6-7: Hard (10 problems)

**Daily Routine:**
1. Read problem description
2. Understand test cases
3. Think about approach (15 min)
4. Implement solution
5. Run tests
6. Optimize if needed
7. Review time/space complexity

**Tips:**
- Start with brute force, then optimize
- Draw diagrams for complex problems
- Test edge cases
- Explain solution out loud
