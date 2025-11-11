# Test-Driven Development Toolchain

## Core Testing Framework

### Google Test (Recommended)
```bash
# Install Google Test
sudo apt-get install libgtest-dev libgmock-dev

# Or use vcpkg/conan for cross-platform
vcpkg install gtest gmock
```

### Catch2 (Alternative - Header-only)
```bash
# Single header include
wget https://github.com/catchorg/Catch2/releases/download/v3.4.0/catch_amalgamated.hpp
```

## Build System - CMake
```cmake
# CMakeLists.txt template
cmake_minimum_required(VERSION 3.20)
project(cpp_mastery_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)
```

## Code Coverage Tools
```bash
# Install coverage tools
sudo apt-get install gcov lcov

# Generate coverage
gcov --version
lcov --version
```

## Static Analysis
```bash
# Clang-tidy for static analysis
sudo apt-get install clang-tidy

# Cppcheck for additional checks
sudo apt-get install cppcheck
```

## Memory Testing
```bash
# Valgrind for memory leak detection
sudo apt-get install valgrind

# AddressSanitizer (built into GCC/Clang)
# Use with -fsanitize=address flag
```

## Performance Profiling
```bash
# Google Benchmark
sudo apt-get install libbenchmark-dev

# Or build from source
git clone https://github.com/google/benchmark.git
```

## Continuous Integration Tools
- **GitHub Actions** - For automated testing
- **Pre-commit hooks** - Run tests before commits
- **CTest** - CMake's testing framework

## IDE Integration
- **VS Code**: C++ TestMate extension
- **CLion**: Built-in test runner
- **Visual Studio**: Native test integration

## Recommended Stack
1. **Testing**: Google Test + Google Mock
2. **Build**: CMake + Ninja
3. **Coverage**: gcov + lcov
4. **Analysis**: clang-tidy + cppcheck
5. **Memory**: Valgrind + AddressSanitizer
6. **Benchmarks**: Google Benchmark
7. **CI/CD**: GitHub Actions
