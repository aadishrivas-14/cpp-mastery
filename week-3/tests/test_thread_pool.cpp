#include <gtest/gtest.h>
#include <future>
#include <chrono>
#include <atomic>
#include "thread_pool.h"
#include "work_stealing_queue.h"

class ThreadPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
        pool = std::make_unique<ThreadPool>(4);
    }
    
    void TearDown() override {
        pool.reset();
    }
    
    std::unique_ptr<ThreadPool> pool;
};

// Basic functionality tests
TEST_F(ThreadPoolTest, SubmitSimpleTask) {
    auto future = pool->submit([]() { return 42; });
    
    EXPECT_EQ(future.get(), 42);
}

TEST_F(ThreadPoolTest, SubmitTaskWithParameters) {
    auto future = pool->submit([](int a, int b) { return a + b; }, 10, 20);
    
    EXPECT_EQ(future.get(), 30);
}

TEST_F(ThreadPoolTest, SubmitMultipleTasks) {
    std::vector<std::future<int>> futures;
    
    for (int i = 0; i < 10; ++i) {
        futures.push_back(pool->submit([i]() { return i * i; }));
    }
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(futures[i].get(), i * i);
    }
}

TEST_F(ThreadPoolTest, TasksExecuteInParallel) {
    std::atomic<int> counter{0};
    std::vector<std::future<void>> futures;
    
    auto start_time = std::chrono::steady_clock::now();
    
    // Submit 4 tasks that each sleep for 100ms
    for (int i = 0; i < 4; ++i) {
        futures.push_back(pool->submit([&counter]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            counter++;
        }));
    }
    
    // Wait for all tasks
    for (auto& future : futures) {
        future.get();
    }
    
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    EXPECT_EQ(counter.load(), 4);
    // Should complete in ~100ms (parallel) rather than ~400ms (sequential)
    EXPECT_LT(duration.count(), 200);
}

TEST_F(ThreadPoolTest, HandlesExceptions) {
    auto future = pool->submit([]() -> int {
        throw std::runtime_error("Test exception");
        return 42;
    });
    
    EXPECT_THROW(future.get(), std::runtime_error);
}

TEST_F(ThreadPoolTest, TasksWithDifferentReturnTypes) {
    auto int_future = pool->submit([]() { return 42; });
    auto string_future = pool->submit([]() { return std::string("hello"); });
    auto void_future = pool->submit([]() { /* do nothing */ });
    
    EXPECT_EQ(int_future.get(), 42);
    EXPECT_EQ(string_future.get(), "hello");
    EXPECT_NO_THROW(void_future.get());
}

// Work stealing tests
class WorkStealingQueueTest : public ::testing::Test {
protected:
    WorkStealingQueue<int> queue;
};

TEST_F(WorkStealingQueueTest, PushAndPop) {
    queue.push(42);
    
    int value;
    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 42);
    
    EXPECT_FALSE(queue.try_pop(value));
}

TEST_F(WorkStealingQueueTest, LIFO_Order) {
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    int value;
    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 3); // Last in, first out
    
    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 2);
    
    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 1);
}

TEST_F(WorkStealingQueueTest, StealFromOtherEnd) {
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    int value;
    EXPECT_TRUE(queue.try_steal(value));
    EXPECT_EQ(value, 1); // Steal from front (FIFO for stealing)
    
    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 3); // Pop from back (LIFO for owner)
    
    EXPECT_TRUE(queue.try_steal(value));
    EXPECT_EQ(value, 2);
}

TEST_F(WorkStealingQueueTest, ConcurrentAccess) {
    const int NUM_ITEMS = 1000;
    std::atomic<int> push_count{0};
    std::atomic<int> pop_count{0};
    std::atomic<int> steal_count{0};
    
    // Producer thread
    std::thread producer([&]() {
        for (int i = 0; i < NUM_ITEMS; ++i) {
            queue.push(i);
            push_count++;
        }
    });
    
    // Consumer thread (owner)
    std::thread consumer([&]() {
        int value;
        while (pop_count.load() + steal_count.load() < NUM_ITEMS) {
            if (queue.try_pop(value)) {
                pop_count++;
            } else {
                std::this_thread::yield();
            }
        }
    });
    
    // Thief thread
    std::thread thief([&]() {
        int value;
        while (pop_count.load() + steal_count.load() < NUM_ITEMS) {
            if (queue.try_steal(value)) {
                steal_count++;
            } else {
                std::this_thread::yield();
            }
        }
    });
    
    producer.join();
    consumer.join();
    thief.join();
    
    EXPECT_EQ(push_count.load(), NUM_ITEMS);
    EXPECT_EQ(pop_count.load() + steal_count.load(), NUM_ITEMS);
}

// Priority task tests
class PriorityThreadPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
        pool = std::make_unique<PriorityThreadPool>(2);
    }
    
    std::unique_ptr<PriorityThreadPool> pool;
};

TEST_F(PriorityThreadPoolTest, ExecutesHighPriorityFirst) {
    std::vector<int> execution_order;
    std::mutex order_mutex;
    
    // Submit low priority task first
    auto low_future = pool->submit(Priority::LOW, [&]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(1);
    });
    
    // Submit high priority task second
    auto high_future = pool->submit(Priority::HIGH, [&]() {
        std::lock_guard<std::mutex> lock(order_mutex);
        execution_order.push_back(2);
    });
    
    low_future.get();
    high_future.get();
    
    // High priority task should execute first despite being submitted second
    EXPECT_EQ(execution_order[0], 2);
    EXPECT_EQ(execution_order[1], 1);
}

// Thread pool with work stealing
class WorkStealingThreadPoolTest : public ::testing::Test {
protected:
    void SetUp() override {
        pool = std::make_unique<WorkStealingThreadPool>(4);
    }
    
    std::unique_ptr<WorkStealingThreadPool> pool;
};

TEST_F(WorkStealingThreadPoolTest, DistributesWorkEvenly) {
    const int NUM_TASKS = 100;
    std::atomic<int> completed_tasks{0};
    std::vector<std::future<void>> futures;
    
    for (int i = 0; i < NUM_TASKS; ++i) {
        futures.push_back(pool->submit([&completed_tasks]() {
            // Simulate some work
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            completed_tasks++;
        }));
    }
    
    // Wait for all tasks
    for (auto& future : futures) {
        future.get();
    }
    
    EXPECT_EQ(completed_tasks.load(), NUM_TASKS);
    
    // Check that work was distributed among threads
    auto thread_stats = pool->getThreadStatistics();
    EXPECT_EQ(thread_stats.size(), 4);
    
    int total_tasks_executed = 0;
    for (const auto& stats : thread_stats) {
        total_tasks_executed += stats.tasks_executed;
    }
    EXPECT_EQ(total_tasks_executed, NUM_TASKS);
}

TEST_F(WorkStealingThreadPoolTest, WorkStealingOccurs) {
    // Create an imbalanced workload
    std::vector<std::future<void>> futures;
    
    // Submit many quick tasks to one thread
    for (int i = 0; i < 50; ++i) {
        futures.push_back(pool->submit([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }));
    }
    
    // Submit one long task
    futures.push_back(pool->submit([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }));
    
    // Wait for all tasks
    for (auto& future : futures) {
        future.get();
    }
    
    auto thread_stats = pool->getThreadStatistics();
    
    // Check that work stealing occurred
    bool work_stealing_occurred = false;
    for (const auto& stats : thread_stats) {
        if (stats.tasks_stolen > 0) {
            work_stealing_occurred = true;
            break;
        }
    }
    
    EXPECT_TRUE(work_stealing_occurred);
}

// Performance tests
TEST_F(ThreadPoolTest, PerformanceComparison) {
    const int NUM_TASKS = 10000;
    
    // Test thread pool performance
    auto start = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::future<int>> futures;
        for (int i = 0; i < NUM_TASKS; ++i) {
            futures.push_back(pool->submit([i]() { return i * i; }));
        }
        
        for (auto& future : futures) {
            future.get();
        }
    }
    auto pool_time = std::chrono::high_resolution_clock::now() - start;
    
    // Test sequential performance
    start = std::chrono::high_resolution_clock::now();
    {
        std::vector<int> results;
        for (int i = 0; i < NUM_TASKS; ++i) {
            results.push_back(i * i);
        }
    }
    auto sequential_time = std::chrono::high_resolution_clock::now() - start;
    
    // Thread pool should handle the overhead reasonably
    // (This test mainly ensures no catastrophic performance regression)
    EXPECT_LT(pool_time.count(), sequential_time.count() * 10);
}

// Shutdown and cleanup tests
TEST_F(ThreadPoolTest, GracefulShutdown) {
    std::atomic<int> completed_tasks{0};
    std::vector<std::future<void>> futures;
    
    // Submit some long-running tasks
    for (int i = 0; i < 10; ++i) {
        futures.push_back(pool->submit([&completed_tasks]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            completed_tasks++;
        }));
    }
    
    // Shutdown should wait for running tasks to complete
    pool.reset();
    
    EXPECT_EQ(completed_tasks.load(), 10);
}

TEST_F(ThreadPoolTest, TaskSubmissionAfterShutdown) {
    pool->shutdown();
    
    EXPECT_THROW(pool->submit([]() { return 42; }), std::runtime_error);
}

// Thread safety tests
TEST_F(ThreadPoolTest, ThreadSafety) {
    const int NUM_THREADS = 10;
    const int TASKS_PER_THREAD = 100;
    std::atomic<int> total_completed{0};
    
    std::vector<std::thread> submitter_threads;
    
    for (int t = 0; t < NUM_THREADS; ++t) {
        submitter_threads.emplace_back([&, t]() {
            std::vector<std::future<void>> futures;
            
            for (int i = 0; i < TASKS_PER_THREAD; ++i) {
                futures.push_back(pool->submit([&total_completed]() {
                    total_completed++;
                }));
            }
            
            for (auto& future : futures) {
                future.get();
            }
        });
    }
    
    for (auto& thread : submitter_threads) {
        thread.join();
    }
    
    EXPECT_EQ(total_completed.load(), NUM_THREADS * TASKS_PER_THREAD);
}
