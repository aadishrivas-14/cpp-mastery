#pragma once

#include <atomic>

/**
 * TODO: Implement a Lock-Free Queue
 * 
 * Requirements:
 * - Method: void push(T value)
 * - Method: bool pop(T& value)
 * - Thread-safe without locks
 * 
 * Implementation hints:
 * - Use std::atomic for lock-free operations
 * - Implement using linked list with atomic head/tail pointers
 * - Use compare_and_swap (CAS) operations
 * - Handle ABA problem if needed
 * 
 * Simplified approach:
 * - Start with a simple atomic counter-based circular buffer
 * - Use std::atomic<size_t> for head and tail indices
 */

template <typename T>
class LockFreeQueue {
 public:
  // TODO: Implement constructor
  // LockFreeQueue(size_t capacity = 1024);
  
  // TODO: Implement push
  // void push(const T& value);
  
  // TODO: Implement pop
  // bool pop(T& value);
  
  // TODO: Implement size
  // size_t size() const;
  
 private:
  // TODO: Add member variables:
  // - T* buffer_;
  // - size_t capacity_;
  // - std::atomic<size_t> head_;
  // - std::atomic<size_t> tail_;
};
