#include "stl_benchmark.h"
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>

TEST(Day1STLBenchmarkTest, VectorInsert) {
  STLBenchmark bench;
  long long time = bench.benchmarkInsert<std::vector<int>>(1000);
  EXPECT_GT(time, 0);
}

TEST(Day1STLBenchmarkTest, ListInsert) {
  STLBenchmark bench;
  long long time = bench.benchmarkInsert<std::list<int>>(1000);
  EXPECT_GT(time, 0);
}

TEST(Day1STLBenchmarkTest, DequeInsert) {
  STLBenchmark bench;
  long long time = bench.benchmarkInsert<std::deque<int>>(1000);
  EXPECT_GT(time, 0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
