#pragma once
#include <chrono>

/**
 * TODO: Implement STL Container Benchmarking
 * 
 * Requirements:
 * - benchmarkInsert<Container>(count) - Measure insertion time
 * - Test with std::vector, std::list, std::deque
 * - Return time in microseconds
 * 
 * Implementation:
 * - Use std::chrono for timing
 * - Template function to work with any container
 * - Push count elements and measure time
 */

class STLBenchmark {
 public:
  template <typename Container>
  long long benchmarkInsert(size_t count);
};

template <typename Container>
long long STLBenchmark::benchmarkInsert(size_t count) {
  // TODO: Measure time to insert count elements
  auto start = std::chrono::high_resolution_clock::now();
  
  // TODO: Create container and insert elements
  
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
