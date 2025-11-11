#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include "benchmark_suite.h"
#include "container_benchmarks.h"
#include "algorithm_benchmarks.h"

class STLBenchmarkTest : public ::testing::Test {
protected:
    void SetUp() override {
        suite = std::make_unique<BenchmarkSuite>();
    }
    
    std::unique_ptr<BenchmarkSuite> suite;
    static constexpr size_t TEST_SIZE = 1000;
};

// Benchmark suite functionality tests
TEST_F(STLBenchmarkTest, RegistersAndRunsBenchmarks) {
    bool benchmark_ran = false;
    
    suite->registerBenchmark("test_benchmark", [&benchmark_ran](size_t) {
        benchmark_ran = true;
        return BenchmarkResult{"test", 1.0, 100};
    });
    
    auto results = suite->runBenchmarks(TEST_SIZE);
    
    EXPECT_TRUE(benchmark_ran);
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].name, "test");
}

TEST_F(STLBenchmarkTest, MeasuresExecutionTime) {
    suite->registerBenchmark("timing_test", [](size_t size) {
        std::vector<int> vec;
        for (size_t i = 0; i < size; ++i) {
            vec.push_back(i);
        }
        return BenchmarkResult{"timing_test", 1.0, size};
    });
    
    auto results = suite->runBenchmarks(TEST_SIZE);
    
    EXPECT_GT(results[0].execution_time_ms, 0.0);
    EXPECT_EQ(results[0].operations_count, TEST_SIZE);
}

// Container insertion benchmarks
TEST_F(STLBenchmarkTest, BenchmarksVectorInsertion) {
    ContainerBenchmarks benchmarks;
    
    auto result = benchmarks.benchmarkVectorPushBack(TEST_SIZE);
    
    EXPECT_EQ(result.name, "vector_push_back");
    EXPECT_GT(result.execution_time_ms, 0.0);
    EXPECT_EQ(result.operations_count, TEST_SIZE);
}

TEST_F(STLBenchmarkTest, BenchmarksListInsertion) {
    ContainerBenchmarks benchmarks;
    
    auto result = benchmarks.benchmarkListPushBack(TEST_SIZE);
    
    EXPECT_EQ(result.name, "list_push_back");
    EXPECT_GT(result.execution_time_ms, 0.0);
    EXPECT_EQ(result.operations_count, TEST_SIZE);
}

TEST_F(STLBenchmarkTest, BenchmarksDequeInsertion) {
    ContainerBenchmarks benchmarks;
    
    auto result = benchmarks.benchmarkDequePushBack(TEST_SIZE);
    
    EXPECT_EQ(result.name, "deque_push_back");
    EXPECT_GT(result.execution_time_ms, 0.0);
    EXPECT_EQ(result.operations_count, TEST_SIZE);
}

// Container access benchmarks
TEST_F(STLBenchmarkTest, BenchmarksRandomAccess) {
    ContainerBenchmarks benchmarks;
    
    auto vector_result = benchmarks.benchmarkVectorRandomAccess(TEST_SIZE);
    auto deque_result = benchmarks.benchmarkDequeRandomAccess(TEST_SIZE);
    
    EXPECT_GT(vector_result.execution_time_ms, 0.0);
    EXPECT_GT(deque_result.execution_time_ms, 0.0);
    
    // Vector should be faster or equal for random access
    EXPECT_LE(vector_result.execution_time_ms, deque_result.execution_time_ms * 2);
}

TEST_F(STLBenchmarkTest, BenchmarksSequentialAccess) {
    ContainerBenchmarks benchmarks;
    
    auto vector_result = benchmarks.benchmarkVectorSequentialAccess(TEST_SIZE);
    auto list_result = benchmarks.benchmarkListSequentialAccess(TEST_SIZE);
    
    EXPECT_GT(vector_result.execution_time_ms, 0.0);
    EXPECT_GT(list_result.execution_time_ms, 0.0);
}

// Search benchmarks
TEST_F(STLBenchmarkTest, BenchmarksLinearSearch) {
    AlgorithmBenchmarks benchmarks;
    
    auto result = benchmarks.benchmarkLinearSearch(TEST_SIZE);
    
    EXPECT_EQ(result.name, "linear_search");
    EXPECT_GT(result.execution_time_ms, 0.0);
}

TEST_F(STLBenchmarkTest, BenchmarksBinarySearch) {
    AlgorithmBenchmarks benchmarks;
    
    auto result = benchmarks.benchmarkBinarySearch(TEST_SIZE);
    
    EXPECT_EQ(result.name, "binary_search");
    EXPECT_GT(result.execution_time_ms, 0.0);
}

TEST_F(STLBenchmarkTest, BenchmarksSetSearch) {
    AlgorithmBenchmarks benchmarks;
    
    auto set_result = benchmarks.benchmarkSetSearch(TEST_SIZE);
    auto unordered_set_result = benchmarks.benchmarkUnorderedSetSearch(TEST_SIZE);
    
    EXPECT_GT(set_result.execution_time_ms, 0.0);
    EXPECT_GT(unordered_set_result.execution_time_ms, 0.0);
    
    // Unordered set should generally be faster for search
    EXPECT_LE(unordered_set_result.execution_time_ms, set_result.execution_time_ms * 2);
}

// Sorting benchmarks
TEST_F(STLBenchmarkTest, BenchmarksSortingAlgorithms) {
    AlgorithmBenchmarks benchmarks;
    
    auto std_sort_result = benchmarks.benchmarkStdSort(TEST_SIZE);
    auto stable_sort_result = benchmarks.benchmarkStableSort(TEST_SIZE);
    auto partial_sort_result = benchmarks.benchmarkPartialSort(TEST_SIZE, TEST_SIZE / 2);
    
    EXPECT_GT(std_sort_result.execution_time_ms, 0.0);
    EXPECT_GT(stable_sort_result.execution_time_ms, 0.0);
    EXPECT_GT(partial_sort_result.execution_time_ms, 0.0);
    
    // Partial sort should be faster than full sort
    EXPECT_LE(partial_sort_result.execution_time_ms, std_sort_result.execution_time_ms);
}

// Memory usage benchmarks
TEST_F(STLBenchmarkTest, MeasuresMemoryUsage) {
    ContainerBenchmarks benchmarks;
    
    auto vector_memory = benchmarks.measureVectorMemoryUsage(TEST_SIZE);
    auto list_memory = benchmarks.measureListMemoryUsage(TEST_SIZE);
    auto deque_memory = benchmarks.measureDequeMemoryUsage(TEST_SIZE);
    
    EXPECT_GT(vector_memory, 0);
    EXPECT_GT(list_memory, 0);
    EXPECT_GT(deque_memory, 0);
    
    // Vector should use less memory than list (no node overhead)
    EXPECT_LT(vector_memory, list_memory);
}

// Comparison tests
TEST_F(STLBenchmarkTest, ComparesContainerPerformance) {
    ContainerBenchmarks benchmarks;
    
    auto comparison = benchmarks.compareInsertionPerformance(TEST_SIZE);
    
    EXPECT_FALSE(comparison.empty());
    EXPECT_TRUE(comparison.find("vector") != comparison.end());
    EXPECT_TRUE(comparison.find("list") != comparison.end());
    EXPECT_TRUE(comparison.find("deque") != comparison.end());
}

TEST_F(STLBenchmarkTest, ComparesSearchPerformance) {
    AlgorithmBenchmarks benchmarks;
    
    auto comparison = benchmarks.compareSearchPerformance(TEST_SIZE);
    
    EXPECT_FALSE(comparison.empty());
    EXPECT_TRUE(comparison.find("linear_search") != comparison.end());
    EXPECT_TRUE(comparison.find("binary_search") != comparison.end());
    EXPECT_TRUE(comparison.find("set_search") != comparison.end());
    EXPECT_TRUE(comparison.find("unordered_set_search") != comparison.end());
}

// Statistical analysis tests
TEST_F(STLBenchmarkTest, CalculatesStatistics) {
    std::vector<double> times = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    BenchmarkStatistics stats = BenchmarkStatistics::calculate(times);
    
    EXPECT_DOUBLE_EQ(stats.mean, 3.0);
    EXPECT_DOUBLE_EQ(stats.median, 3.0);
    EXPECT_DOUBLE_EQ(stats.min, 1.0);
    EXPECT_DOUBLE_EQ(stats.max, 5.0);
    EXPECT_GT(stats.std_dev, 0.0);
}

TEST_F(STLBenchmarkTest, RunsMultipleIterations) {
    suite->setIterations(5);
    
    suite->registerBenchmark("multi_iteration_test", [](size_t size) {
        std::vector<int> vec(size);
        std::iota(vec.begin(), vec.end(), 0);
        return BenchmarkResult{"multi_iteration_test", 1.0, size};
    });
    
    auto results = suite->runBenchmarks(TEST_SIZE);
    
    EXPECT_EQ(results.size(), 1);
    EXPECT_TRUE(results[0].has_statistics);
    EXPECT_GT(results[0].statistics.mean, 0.0);
}

// Visualization tests
TEST_F(STLBenchmarkTest, GeneratesReport) {
    ContainerBenchmarks benchmarks;
    
    std::vector<BenchmarkResult> results;
    results.push_back(benchmarks.benchmarkVectorPushBack(TEST_SIZE));
    results.push_back(benchmarks.benchmarkListPushBack(TEST_SIZE));
    
    std::string report = BenchmarkReporter::generateReport(results);
    
    EXPECT_FALSE(report.empty());
    EXPECT_TRUE(report.find("vector_push_back") != std::string::npos);
    EXPECT_TRUE(report.find("list_push_back") != std::string::npos);
}

TEST_F(STLBenchmarkTest, GeneratesCSVOutput) {
    ContainerBenchmarks benchmarks;
    
    std::vector<BenchmarkResult> results;
    results.push_back(benchmarks.benchmarkVectorPushBack(TEST_SIZE));
    results.push_back(benchmarks.benchmarkListPushBack(TEST_SIZE));
    
    std::string csv = BenchmarkReporter::generateCSV(results);
    
    EXPECT_FALSE(csv.empty());
    EXPECT_TRUE(csv.find("name,execution_time_ms,operations_count") != std::string::npos);
    EXPECT_TRUE(csv.find("vector_push_back") != std::string::npos);
    EXPECT_TRUE(csv.find("list_push_back") != std::string::npos);
}
