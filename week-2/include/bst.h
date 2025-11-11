#pragma once
#include <cstddef>

/**
 * TODO: Implement Binary Search Tree
 * 
 * Requirements:
 * - insert(val) - Add value maintaining BST property
 * - find(val) - Return true if value exists
 * - remove(val) - Delete value from tree
 * - size() - Return number of nodes
 * - empty() - Return true if tree is empty
 * 
 * BST Property:
 * - Left subtree values < node value
 * - Right subtree values > node value
 * 
 * Implementation hints:
 * - Create Node struct with value, left, right pointers
 * - Use recursive functions for insert/find/remove
 * - For remove: handle 3 cases (leaf, one child, two children)
 * 
 * Advanced (optional):
 * - Implement iterators (in-order traversal)
 * - Balance tree (AVL or Red-Black)
 */

template <typename T>
class BST {
 public:
  BST();
  ~BST();
  
  void insert(const T& val);
  bool find(const T& val) const;
  void remove(const T& val);
  size_t size() const;
  bool empty() const;
  
 private:
  struct Node {
    T value;
    Node* left;
    Node* right;
    Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
  };
  
  Node* root_;
  size_t size_;
  
  // TODO: Add helper methods
  // Node* insertHelper(Node* node, const T& val);
  // bool findHelper(Node* node, const T& val) const;
  // Node* removeHelper(Node* node, const T& val);
  // void destroyTree(Node* node);
};

// Template implementation
template <typename T>
BST<T>::BST() : root_(nullptr), size_(0) {}

template <typename T>
BST<T>::~BST() {
  // TODO: Delete all nodes (use recursive helper)
}

template <typename T>
void BST<T>::insert(const T& val) {
  // TODO: Insert value maintaining BST property
  // Increment size_
}

template <typename T>
bool BST<T>::find(const T& val) const {
  // TODO: Search for value in tree
  return false;
}

template <typename T>
void BST<T>::remove(const T& val) {
  // TODO: Remove value from tree
  // Decrement size_ if found
}

template <typename T>
size_t BST<T>::size() const {
  return size_;
}

template <typename T>
bool BST<T>::empty() const {
  return size_ == 0;
}
