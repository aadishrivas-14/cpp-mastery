#pragma once
#include <chrono>

/**
 * TODO: Implement Performance Measurement Tool
 * 
 * Requirements:
 * - measure(func) - Execute function and return time in microseconds
 * - Works with any callable (function, lambda, functor)
 * 
 * Use std::chrono for high-resolution timing
 */

class PerformanceAnalyzer {
 public:
  template <typename Func>
  long long measure(Func f);
};

template <typename Func>
long long PerformanceAnalyzer::measure(Func f) {
  // TODO: Measure execution time of function f
  auto start = std::chrono::high_resolution_clock::now();
  f();
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
