#pragma once

#include <vector>

/**
 * TODO: Implement Advanced Algorithms
 * 
 * Required algorithms:
 * 1. Quick Sort
 * 2. Merge Sort
 * 3. Binary Search
 * 4. Graph DFS/BFS
 * 5. Dynamic Programming example (e.g., Fibonacci, Knapsack)
 * 
 * Implement at least 3 algorithms
 */

// TODO: Implement sorting algorithms
template <typename T>
void quickSort(std::vector<T>& arr, int low, int high);

template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right);

// TODO: Implement search algorithms
template <typename T>
int binarySearch(const std::vector<T>& arr, const T& target);
