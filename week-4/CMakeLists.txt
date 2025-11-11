cmake_minimum_required(VERSION 3.20)
project(week4_projects CXX)

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
  src/http_server.cpp
  src/orm.cpp
  src/cache.cpp
  src/microservice.cpp
  src/realtime.cpp
  src/monitoring.cpp
  src/portfolio.cpp
)

# Create a library from sources
add_library(week4_lib ${SOURCES})
target_link_libraries(week4_lib pthread)

# Enable testing
enable_testing()

# Get all test files
file(GLOB TEST_SOURCES tests/*.cpp)

# Create executable for each test file
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} week4_lib gtest_main pthread)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
