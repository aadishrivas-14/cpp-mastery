cmake_minimum_required(VERSION 3.20)
project(cpp_mastery VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(ENABLE_TESTING "Enable testing" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)
option(ENABLE_BENCHMARKS "Enable benchmarks" ON)
option(ENABLE_STATIC_ANALYSIS "Enable static analysis" ON)

# Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Coverage flags
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Sanitizer flags for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined")
endif()

# Find packages
find_package(PkgConfig REQUIRED)

# Testing framework
if(ENABLE_TESTING)
    find_package(GTest REQUIRED)
    find_package(GMock REQUIRED)
    enable_testing()
    include(GoogleTest)
endif()

# Benchmarking
if(ENABLE_BENCHMARKS)
    find_package(benchmark REQUIRED)
endif()

# Database libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)
find_package(PostgreSQL REQUIRED)

# Networking libraries
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

# JSON library
find_package(nlohmann_json REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories for each week
add_subdirectory(week-1)
add_subdirectory(week-2)
add_subdirectory(week-3)
add_subdirectory(week-4)

# Global test target
if(ENABLE_TESTING)
    add_custom_target(test-all
        COMMAND ctest --output-on-failure
        DEPENDS all-tests
        COMMENT "Running all tests"
    )
endif()

# Coverage target
if(ENABLE_COVERAGE)
    add_custom_target(coverage
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
        COMMAND lcov --list coverage.info
        COMMAND genhtml coverage.info --output-directory coverage-html
        DEPENDS test-all
        COMMENT "Generating code coverage report"
    )
endif()

# Static analysis target
if(ENABLE_STATIC_ANALYSIS)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        add_custom_target(static-analysis
            COMMAND find ${CMAKE_SOURCE_DIR} -name "*.cpp" -o -name "*.h" | xargs clang-tidy
            COMMENT "Running static analysis"
        )
    endif()
    
    find_program(CPPCHECK_EXE NAMES "cppcheck")
    if(CPPCHECK_EXE)
        add_custom_target(cppcheck
            COMMAND cppcheck --enable=all --std=c++20 --project=${CMAKE_BINARY_DIR}/compile_commands.json
            COMMENT "Running cppcheck"
        )
    endif()
endif()

# Memory check target
add_custom_target(memcheck
    COMMAND valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ctest
    DEPENDS all-tests
    COMMENT "Running memory checks"
)
