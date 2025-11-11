#pragma once
#include <vector>

/**
 * TODO: Implement Template Container Classes
 * 
 * Vector<T>:
 * - Dynamic array wrapper
 * - operator[] for access
 * - size() method
 * 
 * Stack<T>:
 * - LIFO data structure
 * - push(), pop(), top()
 * - empty(), size()
 */

template <typename T>
class Vector {
 public:
  explicit Vector(size_t size) : data_(size) {}
  T& operator[](size_t i) { return data_[i]; }
  const T& operator[](size_t i) const { return data_[i]; }
  size_t size() const { return data_.size(); }
 private:
  std::vector<T> data_;
};

template <typename T>
class Stack {
 public:
  void push(const T& val) { data_.push_back(val); }
  void pop() { data_.pop_back(); }
  T& top() { return data_.back(); }
  bool empty() const { return data_.empty(); }
  size_t size() const { return data_.size(); }
 private:
  std::vector<T> data_;
};
