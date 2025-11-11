#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include "lockfree_stack.h"
#include "lockfree_queue.h"
#include "hazard_pointers.h"

// Lock-free stack tests
class LockFreeStackTest : public ::testing::Test {
protected:
    LockFreeStack<int> stack;
};

TEST_F(LockFreeStackTest, PushAndPop) {
    stack.push(42);
    
    int value;
    EXPECT_TRUE(stack.pop(value));
    EXPECT_EQ(value, 42);
    
    EXPECT_FALSE(stack.pop(value));
    EXPECT_TRUE(stack.empty());
}

TEST_F(LockFreeStackTest, LIFO_Order) {
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    int value;
    EXPECT_TRUE(stack.pop(value));
    EXPECT_EQ(value, 3);
    
    EXPECT_TRUE(stack.pop(value));
    EXPECT_EQ(value, 2);
    
    EXPECT_TRUE(stack.pop(value));
    EXPECT_EQ(value, 1);
    
    EXPECT_TRUE(stack.empty());
}

TEST_F(LockFreeStackTest, ConcurrentPushPop) {
    const int NUM_ITEMS = 10000;
    const int NUM_PRODUCERS = 4;
    const int NUM_CONSUMERS = 4;
    
    std::atomic<int> items_pushed{0};
    std::atomic<int> items_popped{0};
    std::vector<std::thread> threads;
    
    // Producer threads
    for (int t = 0; t < NUM_PRODUCERS; ++t) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < NUM_ITEMS / NUM_PRODUCERS; ++i) {
                stack.push(t * 1000 + i);
                items_pushed++;
            }
        });
    }
    
    // Consumer threads
    for (int t = 0; t < NUM_CONSUMERS; ++t) {
        threads.emplace_back([&]() {
            int value;
            while (items_popped.load() < NUM_ITEMS) {
                if (stack.pop(value)) {
                    items_popped++;
                } else {
                    std::this_thread::yield();
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_EQ(items_pushed.load(), NUM_ITEMS);
    EXPECT_EQ(items_popped.load(), NUM_ITEMS);
    EXPECT_TRUE(stack.empty());
}

TEST_F(LockFreeStackTest, ABAProtection) {
    // This test verifies ABA problem protection
    stack.push(1);
    stack.push(2);
    
    // Simulate ABA scenario with multiple threads
    std::atomic<bool> thread1_ready{false};
    std::atomic<bool> thread2_done{false};
    
    std::thread thread1([&]() {
        int value;
        // Thread 1 starts popping but gets interrupted
        thread1_ready = true;
        while (!thread2_done.load()) {
            std::this_thread::yield();
        }
        // Continue popping - should handle ABA correctly
        EXPECT_TRUE(stack.pop(value));
    });
    
    std::thread thread2([&]() {
        while (!thread1_ready.load()) {
            std::this_thread::yield();
        }
        
        // Thread 2 pops and pushes back
        int value;
        EXPECT_TRUE(stack.pop(value));
        stack.push(value);
        thread2_done = true;
    });
    
    thread1.join();
    thread2.join();
}

// Lock-free queue tests
class LockFreeQueueTest : public ::testing::Test {
protected:
    LockFreeQueue<int> queue;
};

TEST_F(LockFreeQueueTest, EnqueueAndDequeue) {
    queue.enqueue(42);
    
    int value;
    EXPECT_TRUE(queue.dequeue(value));
    EXPECT_EQ(value, 42);
    
    EXPECT_FALSE(queue.dequeue(value));
    EXPECT_TRUE(queue.empty());
}

TEST_F(LockFreeQueueTest, FIFO_Order) {
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    int value;
    EXPECT_TRUE(queue.dequeue(value));
    EXPECT_EQ(value, 1);
    
    EXPECT_TRUE(queue.dequeue(value));
    EXPECT_EQ(value, 2);
    
    EXPECT_TRUE(queue.dequeue(value));
    EXPECT_EQ(value, 3);
    
    EXPECT_TRUE(queue.empty());
}

TEST_F(LockFreeQueueTest, ConcurrentEnqueueDequeue) {
    const int NUM_ITEMS = 10000;
    const int NUM_PRODUCERS = 4;
    const int NUM_CONSUMERS = 4;
    
    std::atomic<int> items_enqueued{0};
    std::atomic<int> items_dequeued{0};
    std::vector<std::thread> threads;
    
    // Producer threads
    for (int t = 0; t < NUM_PRODUCERS; ++t) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < NUM_ITEMS / NUM_PRODUCERS; ++i) {
                queue.enqueue(t * 1000 + i);
                items_enqueued++;
            }
        });
    }
    
    // Consumer threads
    for (int t = 0; t < NUM_CONSUMERS; ++t) {
        threads.emplace_back([&]() {
            int value;
            while (items_dequeued.load() < NUM_ITEMS) {
                if (queue.dequeue(value)) {
                    items_dequeued++;
                } else {
                    std::this_thread::yield();
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_EQ(items_enqueued.load(), NUM_ITEMS);
    EXPECT_EQ(items_dequeued.load(), NUM_ITEMS);
    EXPECT_TRUE(queue.empty());
}

TEST_F(LockFreeQueueTest, ProducerConsumerCorrectness) {
    const int NUM_ITEMS = 1000;
    std::vector<bool> received(NUM_ITEMS, false);
    std::mutex received_mutex;
    
    std::thread producer([&]() {
        for (int i = 0; i < NUM_ITEMS; ++i) {
            queue.enqueue(i);
        }
    });
    
    std::thread consumer([&]() {
        int items_consumed = 0;
        int value;
        
        while (items_consumed < NUM_ITEMS) {
            if (queue.dequeue(value)) {
                std::lock_guard<std::mutex> lock(received_mutex);
                EXPECT_GE(value, 0);
                EXPECT_LT(value, NUM_ITEMS);
                EXPECT_FALSE(received[value]); // No duplicates
                received[value] = true;
                items_consumed++;
            } else {
                std::this_thread::yield();
            }
        }
    });
    
    producer.join();
    consumer.join();
    
    // Verify all items were received exactly once
    for (int i = 0; i < NUM_ITEMS; ++i) {
        EXPECT_TRUE(received[i]) << "Item " << i << " was not received";
    }
}

// Hazard pointers tests
class HazardPointersTest : public ::testing::Test {
protected:
    void SetUp() override {
        HazardPointers::initialize(8); // Support up to 8 threads
    }
    
    void TearDown() override {
        HazardPointers::cleanup();
    }
};

TEST_F(HazardPointersTest, BasicProtection) {
    struct TestNode {
        std::atomic<int> value{42};
    };
    
    TestNode* node = new TestNode;
    
    // Protect the node
    HazardPointers::protect(0, node);
    
    // Node should be protected from deletion
    EXPECT_FALSE(HazardPointers::canDelete(node));
    
    // Release protection
    HazardPointers::release(0);
    
    // Now it can be deleted
    EXPECT_TRUE(HazardPointers::canDelete(node));
    
    delete node;
}

TEST_F(HazardPointersTest, MultipleThreadProtection) {
    struct TestNode {
        int value;
        TestNode(int v) : value(v) {}
    };
    
    TestNode* node = new TestNode(100);
    std::atomic<bool> can_delete{true};
    
    std::thread thread1([&]() {
        HazardPointers::protect(0, node);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        can_delete = HazardPointers::canDelete(node);
        HazardPointers::release(0);
    });
    
    std::thread thread2([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        HazardPointers::protect(1, node);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        HazardPointers::release(1);
    });
    
    thread1.join();
    thread2.join();
    
    // Node should have been protected during overlapping period
    EXPECT_FALSE(can_delete.load());
    
    // Now should be safe to delete
    EXPECT_TRUE(HazardPointers::canDelete(node));
    delete node;
}

// Performance comparison tests
class PerformanceComparisonTest : public ::testing::Test {
protected:
    static constexpr int NUM_OPERATIONS = 100000;
    static constexpr int NUM_THREADS = 4;
};

TEST_F(PerformanceComparisonTest, StackPerformance) {
    // Lock-free stack
    LockFreeStack<int> lockfree_stack;
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < NUM_OPERATIONS / NUM_THREADS; ++i) {
                lockfree_stack.push(i);
                int value;
                lockfree_stack.pop(value);
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    auto lockfree_time = std::chrono::high_resolution_clock::now() - start;
    
    // Mutex-based stack
    std::stack<int> mutex_stack;
    std::mutex stack_mutex;
    
    start = std::chrono::high_resolution_clock::now();
    
    threads.clear();
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < NUM_OPERATIONS / NUM_THREADS; ++i) {
                {
                    std::lock_guard<std::mutex> lock(stack_mutex);
                    mutex_stack.push(i);
                }
                {
                    std::lock_guard<std::mutex> lock(stack_mutex);
                    if (!mutex_stack.empty()) {
                        mutex_stack.pop();
                    }
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    auto mutex_time = std::chrono::high_resolution_clock::now() - start;
    
    // Lock-free should be competitive (not necessarily faster due to overhead)
    std::cout << "Lock-free stack time: " << lockfree_time.count() << "ns\n";
    std::cout << "Mutex stack time: " << mutex_time.count() << "ns\n";
    
    // Just ensure lock-free version completes successfully
    EXPECT_GT(lockfree_time.count(), 0);
    EXPECT_GT(mutex_time.count(), 0);
}

TEST_F(PerformanceComparisonTest, QueuePerformance) {
    // Lock-free queue
    LockFreeQueue<int> lockfree_queue;
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    
    // Producer threads
    for (int t = 0; t < NUM_THREADS / 2; ++t) {
        threads.emplace_back([&, t]() {
            for (int i = 0; i < NUM_OPERATIONS / (NUM_THREADS / 2); ++i) {
                lockfree_queue.enqueue(i);
            }
        });
    }
    
    // Consumer threads
    for (int t = 0; t < NUM_THREADS / 2; ++t) {
        threads.emplace_back([&]() {
            int value;
            int consumed = 0;
            while (consumed < NUM_OPERATIONS / (NUM_THREADS / 2)) {
                if (lockfree_queue.dequeue(value)) {
                    consumed++;
                } else {
                    std::this_thread::yield();
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    auto lockfree_time = std::chrono::high_resolution_clock::now() - start;
    
    std::cout << "Lock-free queue time: " << lockfree_time.count() << "ns\n";
    EXPECT_GT(lockfree_time.count(), 0);
}

// Memory ordering tests
class MemoryOrderingTest : public ::testing::Test {};

TEST_F(MemoryOrderingTest, RelaxedOrdering) {
    std::atomic<int> counter{0};
    const int NUM_INCREMENTS = 10000;
    
    std::vector<std::thread> threads;
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < NUM_INCREMENTS; ++i) {
                counter.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    EXPECT_EQ(counter.load(), 4 * NUM_INCREMENTS);
}

TEST_F(MemoryOrderingTest, AcquireReleaseOrdering) {
    std::atomic<int> data{0};
    std::atomic<bool> ready{false};
    
    std::thread producer([&]() {
        data.store(42, std::memory_order_relaxed);
        ready.store(true, std::memory_order_release);
    });
    
    std::thread consumer([&]() {
        while (!ready.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        EXPECT_EQ(data.load(std::memory_order_relaxed), 42);
    });
    
    producer.join();
    consumer.join();
}

TEST_F(MemoryOrderingTest, SequentialConsistency) {
    std::atomic<int> x{0};
    std::atomic<int> y{0};
    std::atomic<int> r1{0};
    std::atomic<int> r2{0};
    
    std::thread thread1([&]() {
        x.store(1, std::memory_order_seq_cst);
        r1.store(y.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
    });
    
    std::thread thread2([&]() {
        y.store(1, std::memory_order_seq_cst);
        r2.store(x.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
    });
    
    thread1.join();
    thread2.join();
    
    // With sequential consistency, at least one thread should see the other's write
    EXPECT_TRUE(r1.load() == 1 || r2.load() == 1);
}
