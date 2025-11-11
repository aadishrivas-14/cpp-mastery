#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "bst.h"
#include "avl_tree.h"

class BSTTest : public ::testing::Test {
protected:
    BST<int> bst;
};

// Basic BST functionality
TEST_F(BSTTest, InsertAndFind) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(9);
    
    EXPECT_TRUE(bst.find(5));
    EXPECT_TRUE(bst.find(3));
    EXPECT_TRUE(bst.find(7));
    EXPECT_TRUE(bst.find(1));
    EXPECT_TRUE(bst.find(9));
    EXPECT_FALSE(bst.find(4));
    EXPECT_FALSE(bst.find(10));
}

TEST_F(BSTTest, InOrderTraversal) {
    std::vector<int> values = {5, 3, 7, 1, 9, 2, 8};
    for (int val : values) {
        bst.insert(val);
    }
    
    std::vector<int> result;
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        result.push_back(*it);
    }
    
    std::vector<int> expected = {1, 2, 3, 5, 7, 8, 9};
    EXPECT_EQ(result, expected);
}

TEST_F(BSTTest, RangeBasedForLoop) {
    std::vector<int> values = {4, 2, 6, 1, 3, 5, 7};
    for (int val : values) {
        bst.insert(val);
    }
    
    std::vector<int> result;
    for (const auto& value : bst) {
        result.push_back(value);
    }
    
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(result, expected);
}

TEST_F(BSTTest, IteratorIncrement) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    
    auto it = bst.begin();
    EXPECT_EQ(*it, 3);
    
    ++it;
    EXPECT_EQ(*it, 5);
    
    ++it;
    EXPECT_EQ(*it, 7);
    
    ++it;
    EXPECT_EQ(it, bst.end());
}

TEST_F(BSTTest, IteratorDecrement) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    
    auto it = bst.end();
    --it;
    EXPECT_EQ(*it, 7);
    
    --it;
    EXPECT_EQ(*it, 5);
    
    --it;
    EXPECT_EQ(*it, 3);
    
    EXPECT_EQ(it, bst.begin());
}

TEST_F(BSTTest, EmptyTreeIterators) {
    EXPECT_EQ(bst.begin(), bst.end());
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
}

TEST_F(BSTTest, SingleElementTree) {
    bst.insert(42);
    
    EXPECT_FALSE(bst.empty());
    EXPECT_EQ(bst.size(), 1);
    
    auto it = bst.begin();
    EXPECT_EQ(*it, 42);
    
    ++it;
    EXPECT_EQ(it, bst.end());
}

// Deletion tests
TEST_F(BSTTest, DeleteLeafNode) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    
    EXPECT_TRUE(bst.erase(1));
    EXPECT_FALSE(bst.find(1));
    EXPECT_EQ(bst.size(), 3);
    
    std::vector<int> result;
    for (const auto& value : bst) {
        result.push_back(value);
    }
    EXPECT_EQ(result, std::vector<int>({3, 5, 7}));
}

TEST_F(BSTTest, DeleteNodeWithOneChild) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    
    EXPECT_TRUE(bst.erase(3));
    EXPECT_FALSE(bst.find(3));
    EXPECT_EQ(bst.size(), 3);
    
    std::vector<int> result;
    for (const auto& value : bst) {
        result.push_back(value);
    }
    EXPECT_EQ(result, std::vector<int>({1, 5, 7}));
}

TEST_F(BSTTest, DeleteNodeWithTwoChildren) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    
    EXPECT_TRUE(bst.erase(5)); // Root with two children
    EXPECT_FALSE(bst.find(5));
    EXPECT_EQ(bst.size(), 6);
    
    std::vector<int> result;
    for (const auto& value : bst) {
        result.push_back(value);
    }
    EXPECT_EQ(result, std::vector<int>({1, 3, 4, 6, 7, 8}));
}

TEST_F(BSTTest, DeleteNonExistentNode) {
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    
    EXPECT_FALSE(bst.erase(10));
    EXPECT_EQ(bst.size(), 3);
}

// STL algorithm compatibility
TEST_F(BSTTest, STLAlgorithmCompatibility) {
    std::vector<int> values = {5, 3, 7, 1, 9, 2, 8, 4, 6};
    for (int val : values) {
        bst.insert(val);
    }
    
    // std::find
    auto it = std::find(bst.begin(), bst.end(), 5);
    EXPECT_NE(it, bst.end());
    EXPECT_EQ(*it, 5);
    
    // std::count
    int count = std::count(bst.begin(), bst.end(), 5);
    EXPECT_EQ(count, 1);
    
    // std::for_each
    int sum = 0;
    std::for_each(bst.begin(), bst.end(), [&sum](int val) { sum += val; });
    EXPECT_EQ(sum, 45); // 1+2+3+4+5+6+7+8+9
}

// AVL Tree tests
class AVLTreeTest : public ::testing::Test {
protected:
    AVLTree<int> avl;
};

TEST_F(AVLTreeTest, MaintainsBalance) {
    // Insert in ascending order (worst case for regular BST)
    for (int i = 1; i <= 7; ++i) {
        avl.insert(i);
    }
    
    // Tree should be balanced
    EXPECT_LE(avl.getHeight(), 3); // log2(7) ≈ 2.8, so height should be ≤ 3
    
    // Should still maintain BST property
    std::vector<int> result;
    for (const auto& value : avl) {
        result.push_back(value);
    }
    EXPECT_EQ(result, std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
}

TEST_F(AVLTreeTest, LeftRotation) {
    avl.insert(1);
    avl.insert(2);
    avl.insert(3); // Should trigger left rotation
    
    EXPECT_EQ(avl.getRoot()->data, 2);
    EXPECT_EQ(avl.getRoot()->left->data, 1);
    EXPECT_EQ(avl.getRoot()->right->data, 3);
}

TEST_F(AVLTreeTest, RightRotation) {
    avl.insert(3);
    avl.insert(2);
    avl.insert(1); // Should trigger right rotation
    
    EXPECT_EQ(avl.getRoot()->data, 2);
    EXPECT_EQ(avl.getRoot()->left->data, 1);
    EXPECT_EQ(avl.getRoot()->right->data, 3);
}

TEST_F(AVLTreeTest, LeftRightRotation) {
    avl.insert(3);
    avl.insert(1);
    avl.insert(2); // Should trigger left-right rotation
    
    EXPECT_EQ(avl.getRoot()->data, 2);
    EXPECT_EQ(avl.getRoot()->left->data, 1);
    EXPECT_EQ(avl.getRoot()->right->data, 3);
}

TEST_F(AVLTreeTest, RightLeftRotation) {
    avl.insert(1);
    avl.insert(3);
    avl.insert(2); // Should trigger right-left rotation
    
    EXPECT_EQ(avl.getRoot()->data, 2);
    EXPECT_EQ(avl.getRoot()->left->data, 1);
    EXPECT_EQ(avl.getRoot()->right->data, 3);
}

// Performance comparison
TEST_F(AVLTreeTest, PerformanceComparison) {
    BST<int> regular_bst;
    AVLTree<int> avl_tree;
    
    const int NUM_ELEMENTS = 10000;
    
    // Insert elements in ascending order (worst case for BST)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        regular_bst.insert(i);
    }
    auto bst_insert_time = std::chrono::high_resolution_clock::now() - start;
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        avl_tree.insert(i);
    }
    auto avl_insert_time = std::chrono::high_resolution_clock::now() - start;
    
    // Search performance
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        regular_bst.find(NUM_ELEMENTS - 1); // Worst case search
    }
    auto bst_search_time = std::chrono::high_resolution_clock::now() - start;
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        avl_tree.find(NUM_ELEMENTS - 1);
    }
    auto avl_search_time = std::chrono::high_resolution_clock::now() - start;
    
    // AVL should be much faster for search in this worst-case scenario
    EXPECT_LT(avl_search_time.count(), bst_search_time.count() / 10);
}

// Custom comparator tests
TEST(CustomComparatorTest, StringLengthComparator) {
    auto length_compare = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };
    
    BST<std::string, decltype(length_compare)> bst(length_compare);
    
    bst.insert("hello");
    bst.insert("hi");
    bst.insert("world");
    bst.insert("a");
    bst.insert("testing");
    
    std::vector<std::string> result;
    for (const auto& str : bst) {
        result.push_back(str);
    }
    
    // Should be sorted by length
    EXPECT_EQ(result[0].length(), 1); // "a"
    EXPECT_EQ(result[1].length(), 2); // "hi"
    EXPECT_LE(result[2].length(), result[3].length());
}
