#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

/**
 * TODO: Implement a Thread Pool
 * 
 * Requirements:
 * - Constructor: ThreadPool(size_t num_threads)
 * - Method: void enqueue(std::function<void()> task)
 * - Method: void wait() - wait for all tasks to complete
 * - Destructor: Join all threads
 * 
 * Implementation hints:
 * - Use std::vector<std::thread> for worker threads
 * - Use std::queue<std::function<void()>> for task queue
 * - Use std::mutex and std::condition_variable for synchronization
 * - Each worker thread should loop, waiting for tasks
 */

class ThreadPool {
 public:
  // TODO: Implement constructor
  // ThreadPool(size_t num_threads);
  
  // TODO: Implement destructor
  // ~ThreadPool();
  
  // TODO: Implement enqueue method
  // void enqueue(std::function<void()> task);
  
  // TODO: Implement wait method
  // void wait();
  
 private:
  // TODO: Add member variables:
  // - std::vector<std::thread> workers_;
  // - std::queue<std::function<void()>> tasks_;
  // - std::mutex queue_mutex_;
  // - std::condition_variable condition_;
  // - bool stop_;
};
