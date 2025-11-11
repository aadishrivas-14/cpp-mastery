# C++ Coding Guidelines

## Overview
This document defines the coding standards for the C++ Mastery program. All code must follow these guidelines to ensure consistency, maintainability, and quality.

## Naming Conventions

### Classes and Structs
- **PascalCase** for class and struct names
```cpp
class BankAccount {};
struct TreeNode {};
class HttpServer {};
```

### Functions and Methods
- **camelCase** for function and method names
```cpp
void calculateBalance();
int getAccountNumber() const;
void processTransaction();
```

### Variables
- **snake_case** for local variables and parameters
```cpp
int account_balance = 0;
std::string user_name;
double interest_rate;
```

### Constants and Enums
- **UPPER_SNAKE_CASE** for constants and enum values
```cpp
const int MAX_CONNECTIONS = 100;
constexpr double PI = 3.14159;

enum class Status {
  SUCCESS,
  FAILURE,
  PENDING
};
```

### Private/Protected Members
- Suffix with underscore `_`
```cpp
class Account {
 private:
  int balance_;
  std::string owner_name_;
};
```

### Namespaces
- **snake_case** for namespace names
```cpp
namespace banking_system {}
namespace http_server {}
```

### Template Parameters
- **PascalCase** for template type parameters
```cpp
template <typename T, typename Allocator>
class Container {};
```

## Modern C++ Features (C++17/20)

### Use auto for Type Deduction
```cpp
// Good
auto result = calculateSum(a, b);
auto it = container.begin();

// Avoid
int result = calculateSum(a, b);
std::vector<int>::iterator it = container.begin();
```

### Range-Based For Loops
```cpp
// Good
for (const auto& item : items) {
  process(item);
}

// Avoid
for (size_t i = 0; i < items.size(); ++i) {
  process(items[i]);
}
```

### Smart Pointers
```cpp
// Good
auto ptr = std::make_unique<Account>();
auto shared = std::make_shared<Connection>();

// Never use raw pointers for ownership
Account* ptr = new Account();  // ❌
```

### Uniform Initialization
```cpp
// Good
int value{42};
std::vector<int> numbers{1, 2, 3};
Account account{100, "John"};

// Avoid
int value = 42;
std::vector<int> numbers = {1, 2, 3};
```

### constexpr and const
```cpp
// Use constexpr for compile-time constants
constexpr int BUFFER_SIZE = 1024;

// Use const for runtime constants
const std::string config_path = getConfigPath();

// Mark methods const when they don't modify state
int getBalance() const { return balance_; }
```

### Structured Bindings (C++17)
```cpp
auto [key, value] = map.find(id);
auto [min, max] = std::minmax({1, 2, 3, 4});
```

### std::optional (C++17)
```cpp
std::optional<Account> findAccount(int id) {
  if (exists(id)) {
    return Account{id};
  }
  return std::nullopt;
}
```

### std::variant (C++17)
```cpp
using Result = std::variant<int, std::string, Error>;
```

## Code Organization

### Header Files
```cpp
#pragma once

#include <system_headers>  // System headers first
#include <third_party>     // Third-party headers

#include "project_headers.h"  // Project headers last

namespace project_name {

class ClassName {
 public:
  // Public interface first
  
 protected:
  // Protected members
  
 private:
  // Private implementation last
};

}  // namespace project_name
```

### Source Files
```cpp
#include "header.h"  // Corresponding header first

#include <system_headers>
#include "other_project_headers.h"

namespace project_name {

// Implementation

}  // namespace project_name
```

## Formatting Rules

### Line Length
- Maximum 100 characters per line
- Break long lines at logical points

### Indentation
- 2 spaces (no tabs)
- Indent access modifiers by -2

### Braces
- Opening brace on same line (K&R style)
```cpp
if (condition) {
  doSomething();
} else {
  doSomethingElse();
}
```

### Spacing
```cpp
// Space after control keywords
if (condition) {}
for (auto& item : items) {}

// No space for function calls
function(arg1, arg2);

// Space around operators
int result = a + b * c;
```

## Best Practices

### Error Handling
```cpp
// Use exceptions for exceptional cases
throw std::runtime_error("Invalid state");

// Use std::optional for expected failures
std::optional<int> parse(const std::string& str);

// Use std::expected (C++23) or custom Result type
Result<int, Error> divide(int a, int b);
```

### Resource Management (RAII)
```cpp
class FileHandle {
 public:
  FileHandle(const std::string& path) : file_(std::fopen(path.c_str(), "r")) {
    if (!file_) throw std::runtime_error("Failed to open file");
  }
  
  ~FileHandle() {
    if (file_) std::fclose(file_);
  }
  
  // Delete copy, allow move
  FileHandle(const FileHandle&) = delete;
  FileHandle& operator=(const FileHandle&) = delete;
  FileHandle(FileHandle&&) noexcept = default;
  FileHandle& operator=(FileHandle&&) noexcept = default;
  
 private:
  FILE* file_;
};
```

### Move Semantics
```cpp
class Buffer {
 public:
  // Move constructor
  Buffer(Buffer&& other) noexcept 
    : data_(std::exchange(other.data_, nullptr)),
      size_(std::exchange(other.size_, 0)) {}
  
  // Move assignment
  Buffer& operator=(Buffer&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = std::exchange(other.data_, nullptr);
      size_ = std::exchange(other.size_, 0);
    }
    return *this;
  }
};
```

### Rule of Zero/Five
```cpp
// Rule of Zero: Let compiler generate everything
class Simple {
  std::string name_;
  std::vector<int> data_;
};

// Rule of Five: If you define one, define all
class Complex {
 public:
  ~Complex();
  Complex(const Complex&);
  Complex& operator=(const Complex&);
  Complex(Complex&&) noexcept;
  Complex& operator=(Complex&&) noexcept;
};
```

### Const Correctness
```cpp
class Account {
 public:
  // Const methods for read-only operations
  int getBalance() const { return balance_; }
  
  // Non-const for modifications
  void deposit(int amount) { balance_ += amount; }
  
  // Const parameters for input
  void setOwner(const std::string& name) { owner_ = name; }
  
 private:
  int balance_;
  std::string owner_;
};
```

### Avoid Raw Loops
```cpp
// Good: Use algorithms
auto it = std::find_if(items.begin(), items.end(), 
                       [](const auto& item) { return item.isValid(); });

// Good: Use ranges (C++20)
auto valid_items = items | std::views::filter(&Item::isValid);

// Avoid: Manual loops when algorithms exist
for (auto it = items.begin(); it != items.end(); ++it) {
  if (it->isValid()) {
    return it;
  }
}
```

## Performance Guidelines

### Pass by Value vs Reference
```cpp
// Small types: pass by value
void process(int value);

// Large types: pass by const reference
void process(const std::vector<int>& data);

// Sink arguments: pass by value and move
void setData(std::vector<int> data) {
  data_ = std::move(data);
}
```

### Reserve Capacity
```cpp
std::vector<int> numbers;
numbers.reserve(1000);  // Avoid reallocations
```

### Avoid Unnecessary Copies
```cpp
// Good
const auto& item = container[i];

// Bad
auto item = container[i];  // Unnecessary copy
```

### Use emplace over push
```cpp
// Good
vec.emplace_back(arg1, arg2);

// Less efficient
vec.push_back(Type{arg1, arg2});
```

## Documentation

### File Headers
```cpp
/**
 * @file calculator.h
 * @brief Basic calculator implementation
 * @author Aditya Shrivas
 */
```

### Class Documentation
```cpp
/**
 * @brief Manages bank account operations
 * 
 * Provides thread-safe operations for deposits, withdrawals,
 * and balance queries.
 */
class BankAccount {
```

### Function Documentation
```cpp
/**
 * @brief Calculates compound interest
 * @param principal Initial amount
 * @param rate Annual interest rate (as decimal)
 * @param years Number of years
 * @return Final amount after interest
 */
double calculateCompoundInterest(double principal, double rate, int years);
```

## Testing Guidelines

### Test Naming
```cpp
TEST(CalculatorTest, AdditionReturnsCorrectSum) {
  Calculator calc;
  EXPECT_EQ(calc.add(2, 3), 5);
}

TEST(BankAccountTest, WithdrawFailsWhenInsufficientFunds) {
  BankAccount account{100};
  EXPECT_FALSE(account.withdraw(200));
}
```

### Test Structure (AAA Pattern)
```cpp
TEST(AccountTest, DepositIncreasesBalance) {
  // Arrange
  BankAccount account{100};
  
  // Act
  account.deposit(50);
  
  // Assert
  EXPECT_EQ(account.getBalance(), 150);
}
```

## Code Quality Tools

### Automated Checks
All code must pass:
- `clang-format` - Code formatting
- `clang-tidy` - Static analysis
- `cppcheck` - Additional static analysis
- `valgrind` - Memory leak detection
- `AddressSanitizer` - Runtime error detection

### Pre-commit Hooks
Run before every commit:
```bash
pre-commit run --all-files
```

### Manual Checks
```bash
# Format code
clang-format -i src/*.cpp include/*.h

# Lint code
clang-tidy src/*.cpp -- -Iinclude

# Static analysis
cppcheck --enable=all --suppress=missingInclude src/

# Memory check
valgrind --leak-check=full ./build/program
```

## Git Commit Messages

### Format
```
<type>(<scope>): <subject>

<body>

<footer>
```

### Types
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `test`: Test additions/changes
- `refactor`: Code refactoring
- `perf`: Performance improvements
- `style`: Formatting changes
- `build`: Build system changes

### Examples
```
feat(calculator): add expression parser

Implement recursive descent parser for arithmetic expressions
with support for parentheses and operator precedence.

Closes #123
```

```
fix(banking): prevent negative balance

Add validation to ensure withdrawals cannot result in
negative account balance.
```

## Anti-Patterns to Avoid

### Don't Use
- `using namespace std;` in headers
- Raw `new`/`delete` (use smart pointers)
- C-style casts (use `static_cast`, etc.)
- `NULL` (use `nullptr`)
- `#define` for constants (use `constexpr`)
- Manual memory management (use RAII)
- Mutable global state
- `goto` statements
- Multiple return types via output parameters

### Prefer
- Stack allocation over heap
- Algorithms over raw loops
- `std::array` over C arrays
- `std::string` over `char*`
- Scoped enums (`enum class`) over plain enums
- `= delete` over private undefined functions
- `override` keyword for virtual functions
- `final` keyword when appropriate

## Project-Specific Standards

### Directory Structure
```
project_name/
├── include/           # Public headers
├── src/              # Implementation files
├── tests/            # Test files
├── benchmarks/       # Performance benchmarks
└── CMakeLists.txt    # Build configuration
```

### Build Configuration
- Minimum C++17, prefer C++20
- Enable all warnings: `-Wall -Wextra -Wpedantic`
- Treat warnings as errors: `-Werror`
- Enable optimizations for release: `-O3`
- Enable debug symbols: `-g`

### Dependencies
- Prefer standard library over third-party
- Document all external dependencies
- Use CMake FetchContent or system packages

## References
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Modern C++ Best Practices](https://github.com/cpp-best-practices/cppbestpractices)
