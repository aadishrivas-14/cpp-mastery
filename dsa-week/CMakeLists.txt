cmake_minimum_required(VERSION 3.20)
project(dsa_week CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Easy Problems
add_executable(test_easy_problems 
  easy/src/problems.cpp
  easy/tests/test_easy_problems.cpp
)
target_link_libraries(test_easy_problems gtest_main pthread)
add_test(NAME EasyProblems COMMAND test_easy_problems)

# Medium Problems (25)
add_executable(test_medium_problems
  medium/src/problems.cpp
  medium/tests/test_medium_problems.cpp
)
target_link_libraries(test_medium_problems gtest_main pthread)
add_test(NAME MediumProblems COMMAND test_medium_problems)

# Hard Problems (10)
add_executable(test_hard_problems
  hard/src/problems.cpp
  hard/tests/test_hard_problems.cpp
)
target_link_libraries(test_hard_problems gtest_main pthread)
add_test(NAME HardProblems COMMAND test_hard_problems)
