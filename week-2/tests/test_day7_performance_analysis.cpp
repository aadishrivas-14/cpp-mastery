#include "performance_analyzer.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Day7PerformanceTest, VectorPerformance) {
  PerformanceAnalyzer analyzer;
  long long time = analyzer.measure([]() {
    std::vector<int> v;
    for (int i = 0; i < 10000; ++i) v.push_back(i);
  });
  EXPECT_GT(time, 0);
}

TEST(Day7PerformanceTest, AllocationPerformance) {
  PerformanceAnalyzer analyzer;
  long long time = analyzer.measure([]() {
    for (int i = 0; i < 1000; ++i) {
      int* p = new int(i);
      delete p;
    }
  });
  EXPECT_GT(time, 0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
