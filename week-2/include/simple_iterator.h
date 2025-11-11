#pragma once

/**
 * TODO: Implement Custom Iterator
 * 
 * Requirements:
 * - operator* - Dereference
 * - operator-> - Member access
 * - operator++ - Increment
 * - operator== and operator!= - Comparison
 * 
 * Iterator should work with raw pointers/arrays
 */

template <typename T>
class SimpleIterator {
 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  
  explicit SimpleIterator(pointer ptr) : ptr_(ptr) {}
  
  reference operator*() const { return *ptr_; }
  pointer operator->() { return ptr_; }
  SimpleIterator& operator++() { ++ptr_; return *this; }
  bool operator==(const SimpleIterator& other) const { return ptr_ == other.ptr_; }
  bool operator!=(const SimpleIterator& other) const { return ptr_ != other.ptr_; }
  
 private:
  pointer ptr_;
};
