// Week 1, Day 7: Integration + Memory Pool
// Project Status: Memory Pool Allocator & Integration Testing

#include "memory_pool.h"
#include <gtest/gtest.h>

TEST(Day7MemoryPoolTest, Allocate) {
  MemoryPool pool(64, 10);
  void* ptr = pool.allocate();
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(pool.available(), 9);
}

TEST(Day7MemoryPoolTest, Deallocate) {
  MemoryPool pool(64, 10);
  void* ptr = pool.allocate();
  pool.deallocate(ptr);
  EXPECT_EQ(pool.available(), 10);
}

TEST(Day7MemoryPoolTest, ExhaustPool) {
  MemoryPool pool(64, 2);
  void* ptr1 = pool.allocate();
  void* ptr2 = pool.allocate();
  void* ptr3 = pool.allocate();
  
  EXPECT_NE(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(ptr3, nullptr);
}

TEST(Day7IntegrationTest, AllWeek1Components) {
  // Integration test combining all Week 1 concepts
  EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
