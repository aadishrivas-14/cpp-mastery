#pragma once
#include <cstddef>

/**
 * TODO: Implement Template Functions and Classes
 * 
 * Function Templates:
 * - max(a, b) - Return larger value
 * - swap(a, b) - Swap two values
 * 
 * Class Template:
 * - Array<T, N> - Fixed-size array
 */

template <typename T>
T max(T a, T b) {
  // TODO: Return the larger value
  return a;
}

template <typename T>
void swap(T& a, T& b) {
  // TODO: Swap values of a and b
}

template <typename T, size_t N>
class Array {
 public:
  T& operator[](size_t i) { return data_[i]; }
  const T& operator[](size_t i) const { return data_[i]; }
  size_t size() const { return N; }
 private:
  T data_[N];
};
