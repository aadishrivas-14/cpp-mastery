// Week 1, Day 6: Smart Pointers + RAII
// Project Status: Smart Pointer Implementation & Resource Manager with RAII

#include "unique_ptr.h"
#include <gtest/gtest.h>

TEST(Day6SmartPointersTest, UniquePtrBasic) {
  UniquePtr<int> ptr(new int(42));
  EXPECT_EQ(*ptr, 42);
}

TEST(Day6SmartPointersTest, UniquePtrMove) {
  UniquePtr<int> ptr1(new int(42));
  UniquePtr<int> ptr2(std::move(ptr1));
  
  EXPECT_EQ(ptr1.get(), nullptr);
  EXPECT_NE(ptr2.get(), nullptr);
  EXPECT_EQ(*ptr2, 42);
}

TEST(Day6RAIITest, ResourceManagement) {
  {
    UniquePtr<Resource> res(new Resource());
    EXPECT_EQ(res->getValue(), 42);
  }
  // Resource automatically deleted
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
