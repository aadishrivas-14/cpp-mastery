cmake_minimum_required(VERSION 3.20)
project(calculator)

# Library
add_library(calculator_lib
    src/calculator.cpp
    src/expression_parser.cpp
)

target_include_directories(calculator_lib PUBLIC include)
target_compile_features(calculator_lib PUBLIC cxx_std_20)

# Executable
add_executable(calculator
    src/main.cpp
)

target_link_libraries(calculator calculator_lib)

# Tests
if(ENABLE_TESTING)
    add_executable(calculator_tests
        tests/test_calculator.cpp
        tests/test_expression_parser.cpp
        tests/test_main.cpp
    )
    
    target_link_libraries(calculator_tests 
        calculator_lib
        GTest::gtest
        GTest::gtest_main
        GMock::gmock
    )
    
    gtest_discover_tests(calculator_tests)
    
    add_custom_target(calculator-tests
        COMMAND calculator_tests
        DEPENDS calculator_tests
        COMMENT "Running calculator tests"
    )
endif()

# Benchmarks
if(ENABLE_BENCHMARKS)
    add_executable(calculator_benchmarks
        benchmarks/benchmark_calculator.cpp
    )
    
    target_link_libraries(calculator_benchmarks
        calculator_lib
        benchmark::benchmark
    )
endif()
