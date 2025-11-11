cmake_minimum_required(VERSION 3.20)
project(week3_projects CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
  src/thread_pool.cpp
  src/lockfree_queue.cpp
  src/modern_features.cpp
  src/patterns.cpp
  src/simd_ops.cpp
  src/algorithms.cpp
  src/trading_engine.cpp
)

# Create a library from sources
add_library(week3_lib ${SOURCES})
target_link_libraries(week3_lib pthread)

# Enable testing
enable_testing()

# Get all test files
file(GLOB TEST_SOURCES tests/*.cpp)

# Create executable for each test file
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} week3_lib gtest_main pthread)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
