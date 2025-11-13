# DSA Week - Easy Problems COMPLETE ✅

## Status: 15/15 Problems Solved - All Tests Passing

**Test Results:** 35/35 tests passed (100%)

---

## Problems Completed

### 1. Two Sum ✅
- **Algorithm:** Hash map for O(n) lookup
- **Time:** O(n) | **Space:** O(n)
- **Key Insight:** Store complements as you iterate

### 2. Valid Parentheses ✅
- **Algorithm:** Stack-based matching
- **Time:** O(n) | **Space:** O(n)
- **Key Insight:** Push opening brackets, pop and match closing

### 3. Merge Two Sorted Lists ✅
- **Algorithm:** Two pointers with dummy node
- **Time:** O(n+m) | **Space:** O(1)
- **Key Insight:** Dummy node simplifies edge cases

### 4. Best Time to Buy/Sell Stock ✅
- **Algorithm:** Single pass tracking min price
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** Track minimum price seen so far

### 5. Valid Palindrome ✅
- **Algorithm:** Two pointers from ends
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** Skip non-alphanumeric, compare case-insensitive

### 6. Maximum Subarray ✅
- **Algorithm:** Kadane's Algorithm
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** current_sum = max(num, current_sum + num)

### 7. Contains Duplicate ✅
- **Algorithm:** Hash set for tracking
- **Time:** O(n) | **Space:** O(n)
- **Key Insight:** Return true on first duplicate found

### 8. Reverse Linked List ✅
- **Algorithm:** Iterative with three pointers
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** prev, current, next pointer manipulation

### 9. Binary Search ✅
- **Algorithm:** Classic binary search
- **Time:** O(log n) | **Space:** O(1)
- **Key Insight:** mid = left + (right - left) / 2 avoids overflow

### 10. Climbing Stairs ✅
- **Algorithm:** Fibonacci sequence
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** ways(n) = ways(n-1) + ways(n-2)

### 11. Symmetric Tree ✅
- **Algorithm:** Recursive mirror check
- **Time:** O(n) | **Space:** O(h)
- **Key Insight:** Compare left.left with right.right, left.right with right.left

### 12. Single Number ✅
- **Algorithm:** XOR bit manipulation
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** a ^ a = 0, a ^ 0 = a (duplicates cancel out)

### 13. Intersection of Two Arrays ✅
- **Algorithm:** Two hash sets
- **Time:** O(n+m) | **Space:** O(min(n,m))
- **Key Insight:** Convert one array to set, check other against it

### 14. Move Zeroes ✅
- **Algorithm:** Two pointers (write position)
- **Time:** O(n) | **Space:** O(1)
- **Key Insight:** Track position for next non-zero element

### 15. Fizz Buzz ✅
- **Algorithm:** Modulo checks
- **Time:** O(n) | **Space:** O(n)
- **Key Insight:** Check % 15 first, then % 3, then % 5

---

## Key Patterns Mastered

✅ **Hash Tables** - Two Sum, Contains Duplicate, Intersection  
✅ **Two Pointers** - Palindrome, Move Zeroes  
✅ **Stack** - Valid Parentheses  
✅ **Linked Lists** - Merge Lists, Reverse List  
✅ **Binary Search** - Classic implementation  
✅ **Dynamic Programming** - Climbing Stairs, Max Subarray  
✅ **Trees** - Symmetric Tree  
✅ **Bit Manipulation** - Single Number (XOR)  
✅ **Greedy** - Best Time to Buy/Sell Stock  

---

## Next Steps

1. **Review and Optimize**
   - Can any solution be improved?
   - Are there alternative approaches?

2. **Medium Problems** (25 problems)
   - More complex variations
   - Multiple pattern combinations
   - Harder edge cases

3. **Hard Problems** (10 problems)
   - Advanced algorithms
   - Complex data structures
   - System design elements

---

## Build & Test Commands

```bash
# Build
cd dsa-week/build
cmake .. && make

# Run all tests
./test_easy_problems

# Run specific problem
./test_easy_problems --gtest_filter="Problem01*"

# Run with verbose output
./test_easy_problems --gtest_print_time=1
```

---

## Time Investment

- **Setup:** 5 minutes
- **Implementation:** ~2 hours (all 15 problems)
- **Testing & Debugging:** 15 minutes
- **Total:** ~2.5 hours

**Average per problem:** 10 minutes

---

## Interview Readiness

These 15 problems cover the most common easy-level questions asked by:
- Amazon
- Google
- Microsoft
- Meta
- Apple
- Bloomberg
- Adobe

You're now ready for easy-level technical interviews! 🚀
