#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include "memory_pool.h"

class MemoryPoolTest : public ::testing::Test {
protected:
    static constexpr size_t POOL_SIZE = 1024;
    static constexpr size_t BLOCK_SIZE = 64;
};

// Basic functionality tests
TEST_F(MemoryPoolTest, AllocatesAndDeallocatesMemory) {
    MemoryPool<int> pool(100);
    
    int* ptr = pool.allocate();
    EXPECT_NE(ptr, nullptr);
    
    *ptr = 42;
    EXPECT_EQ(*ptr, 42);
    
    pool.deallocate(ptr);
    // Should not crash
}

TEST_F(MemoryPoolTest, AllocatesMultipleBlocks) {
    MemoryPool<int> pool(10);
    std::vector<int*> ptrs;
    
    // Allocate multiple blocks
    for (int i = 0; i < 5; ++i) {
        int* ptr = pool.allocate();
        EXPECT_NE(ptr, nullptr);
        *ptr = i;
        ptrs.push_back(ptr);
    }
    
    // Verify values
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(*ptrs[i], i);
    }
    
    // Deallocate all
    for (auto ptr : ptrs) {
        pool.deallocate(ptr);
    }
}

TEST_F(MemoryPoolTest, ReusesFreedMemory) {
    MemoryPool<int> pool(2);
    
    int* ptr1 = pool.allocate();
    int* ptr2 = pool.allocate();
    
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr1, ptr2);
    
    pool.deallocate(ptr1);
    
    int* ptr3 = pool.allocate();
    EXPECT_EQ(ptr3, ptr1); // Should reuse the freed memory
    
    pool.deallocate(ptr2);
    pool.deallocate(ptr3);
}

TEST_F(MemoryPoolTest, HandlesPoolExhaustion) {
    MemoryPool<int> pool(2);
    
    int* ptr1 = pool.allocate();
    int* ptr2 = pool.allocate();
    
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    
    // Pool should be exhausted, but should handle gracefully
    int* ptr3 = pool.allocate();
    EXPECT_NE(ptr3, nullptr); // Should allocate new chunk
    
    pool.deallocate(ptr1);
    pool.deallocate(ptr2);
    pool.deallocate(ptr3);
}

// Alignment tests
TEST_F(MemoryPoolTest, ReturnsAlignedMemory) {
    MemoryPool<double> pool(10);
    
    double* ptr = pool.allocate();
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(ptr) % alignof(double), 0);
    
    pool.deallocate(ptr);
}

TEST_F(MemoryPoolTest, HandlesLargeObjects) {
    struct LargeObject {
        char data[256];
        int value;
    };
    
    MemoryPool<LargeObject> pool(5);
    
    LargeObject* ptr = pool.allocate();
    EXPECT_NE(ptr, nullptr);
    
    ptr->value = 123;
    EXPECT_EQ(ptr->value, 123);
    
    pool.deallocate(ptr);
}

// Performance tests
TEST_F(MemoryPoolTest, PerformanceComparisonWithNewDelete) {
    const int NUM_ALLOCATIONS = 10000;
    
    // Test memory pool performance
    auto start = std::chrono::high_resolution_clock::now();
    {
        MemoryPool<int> pool(NUM_ALLOCATIONS);
        std::vector<int*> ptrs;
        ptrs.reserve(NUM_ALLOCATIONS);
        
        for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
            ptrs.push_back(pool.allocate());
        }
        
        for (auto ptr : ptrs) {
            pool.deallocate(ptr);
        }
    }
    auto pool_time = std::chrono::high_resolution_clock::now() - start;
    
    // Test new/delete performance
    start = std::chrono::high_resolution_clock::now();
    {
        std::vector<int*> ptrs;
        ptrs.reserve(NUM_ALLOCATIONS);
        
        for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
            ptrs.push_back(new int);
        }
        
        for (auto ptr : ptrs) {
            delete ptr;
        }
    }
    auto new_delete_time = std::chrono::high_resolution_clock::now() - start;
    
    // Memory pool should be faster (or at least not significantly slower)
    EXPECT_LE(pool_time.count(), new_delete_time.count() * 2);
}

// Thread safety tests (if implemented)
TEST_F(MemoryPoolTest, ThreadSafetyBasic) {
    ThreadSafeMemoryPool<int> pool(100);
    
    std::vector<std::thread> threads;
    std::vector<std::vector<int*>> thread_ptrs(4);
    
    // Launch multiple threads
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&pool, &thread_ptrs, t]() {
            for (int i = 0; i < 25; ++i) {
                int* ptr = pool.allocate();
                EXPECT_NE(ptr, nullptr);
                *ptr = t * 100 + i;
                thread_ptrs[t].push_back(ptr);
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verify all allocations succeeded
    for (int t = 0; t < 4; ++t) {
        EXPECT_EQ(thread_ptrs[t].size(), 25);
        for (int i = 0; i < 25; ++i) {
            EXPECT_EQ(*thread_ptrs[t][i], t * 100 + i);
            pool.deallocate(thread_ptrs[t][i]);
        }
    }
}

// Memory statistics tests
TEST_F(MemoryPoolTest, TracksMemoryStatistics) {
    MemoryPool<int> pool(10);
    
    EXPECT_EQ(pool.getTotalAllocated(), 0);
    EXPECT_EQ(pool.getTotalDeallocated(), 0);
    EXPECT_GT(pool.getTotalCapacity(), 0);
    
    std::vector<int*> ptrs;
    for (int i = 0; i < 5; ++i) {
        ptrs.push_back(pool.allocate());
    }
    
    EXPECT_EQ(pool.getTotalAllocated(), 5);
    EXPECT_EQ(pool.getAvailableBlocks(), pool.getTotalCapacity() - 5);
    
    for (auto ptr : ptrs) {
        pool.deallocate(ptr);
    }
    
    EXPECT_EQ(pool.getTotalDeallocated(), 5);
    EXPECT_EQ(pool.getAvailableBlocks(), pool.getTotalCapacity());
}

// Custom allocator integration tests
TEST_F(MemoryPoolTest, WorksWithSTLContainers) {
    using PoolAllocator = MemoryPoolAllocator<int>;
    using Vector = std::vector<int, PoolAllocator>;
    
    MemoryPool<int> pool(1000);
    PoolAllocator allocator(&pool);
    
    Vector vec(allocator);
    
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

// Error handling tests
TEST_F(MemoryPoolTest, HandlesNullPointerDeallocation) {
    MemoryPool<int> pool(10);
    
    // Should not crash
    EXPECT_NO_THROW(pool.deallocate(nullptr));
}

TEST_F(MemoryPoolTest, HandlesDoubleFree) {
    MemoryPool<int> pool(10);
    
    int* ptr = pool.allocate();
    pool.deallocate(ptr);
    
    // Double free should be handled gracefully
    EXPECT_NO_THROW(pool.deallocate(ptr));
}
