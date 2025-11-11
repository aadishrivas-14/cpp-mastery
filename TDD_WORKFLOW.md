# Test-Driven Development Workflow

## Environment Setup

### One-Time Setup
```bash
# Setup development environment
./setup-dev-env.sh

# Enter development container
docker-compose run --rm cpp-dev
```

### Daily Development
```bash
# Start services
docker-compose up -d postgres redis

# Enter development shell
docker-compose run --rm cpp-dev
```

## TDD Cycle: Red-Green-Refactor

### 1. Red Phase - Write Failing Test
```cpp
// tests/test_calculator.cpp
#include <gtest/gtest.h>
#include "calculator.h"

TEST(CalculatorTest, AddsTwoNumbers) {
    Calculator calc;
    EXPECT_EQ(calc.add(2, 3), 5);
}
```

### 2. Green Phase - Make Test Pass
```cpp
// src/calculator.cpp
#include "calculator.h"

int Calculator::add(int a, int b) {
    return a + b;
}
```

### 3. Refactor Phase - Improve Code
```cpp
// Refactor for better design, performance, readability
class Calculator {
public:
    template<typename T>
    T add(T a, T b) const noexcept {
        return a + b;
    }
};
```

## Build and Test Commands

### Basic Testing
```bash
# Build and run tests
mkdir -p build && cd build
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug
ninja
ctest --output-on-failure

# Run specific test
ctest -R CalculatorTest
```

### Code Coverage
```bash
# Generate coverage report
docker-compose run --rm coverage

# View coverage in browser
open coverage-html/index.html
```

### Memory Testing
```bash
# Run with Valgrind
docker-compose run --rm cpp-dev bash -c "
cd build && 
cmake .. -DCMAKE_BUILD_TYPE=Debug &&
ninja &&
valgrind --tool=memcheck --leak-check=full ./tests/test_calculator
"
```

### Performance Testing
```bash
# Run benchmarks
cd build
cmake .. -DENABLE_BENCHMARKS=ON
ninja
./benchmarks/benchmark_calculator
```

## Project Structure for TDD

```
week-1/
├── CMakeLists.txt
├── src/
│   ├── calculator.cpp
│   └── calculator.h
├── include/
│   └── calculator.h
├── tests/
│   ├── CMakeLists.txt
│   ├── test_calculator.cpp
│   └── test_main.cpp
└── benchmarks/
    ├── CMakeLists.txt
    └── benchmark_calculator.cpp
```

## Testing Patterns

### Unit Tests
```cpp
// Test single function/method
TEST(CalculatorTest, MultiplyReturnsProduct) {
    Calculator calc;
    EXPECT_EQ(calc.multiply(4, 5), 20);
}
```

### Integration Tests
```cpp
// Test multiple components together
TEST(BankingSystemTest, TransferBetweenAccounts) {
    Bank bank;
    auto account1 = bank.createAccount("Alice", 1000);
    auto account2 = bank.createAccount("Bob", 500);
    
    EXPECT_TRUE(bank.transfer(account1, account2, 200));
    EXPECT_EQ(account1->getBalance(), 800);
    EXPECT_EQ(account2->getBalance(), 700);
}
```

### Parameterized Tests
```cpp
class CalculatorParameterizedTest : public ::testing::TestWithParam<std::tuple<int, int, int>> {};

TEST_P(CalculatorParameterizedTest, Addition) {
    auto [a, b, expected] = GetParam();
    Calculator calc;
    EXPECT_EQ(calc.add(a, b), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AdditionTests,
    CalculatorParameterizedTest,
    ::testing::Values(
        std::make_tuple(1, 2, 3),
        std::make_tuple(0, 0, 0),
        std::make_tuple(-1, 1, 0)
    )
);
```

### Mock Objects
```cpp
#include <gmock/gmock.h>

class MockDatabase {
public:
    MOCK_METHOD(bool, save, (const User& user), ());
    MOCK_METHOD(std::optional<User>, find, (int id), ());
};

TEST(UserServiceTest, SavesUserToDatabase) {
    MockDatabase mockDb;
    UserService service(mockDb);
    User user{"Alice", "alice@example.com"};
    
    EXPECT_CALL(mockDb, save(user))
        .WillOnce(::testing::Return(true));
    
    EXPECT_TRUE(service.createUser(user));
}
```

## Database Testing
```cpp
class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup test database
        db = std::make_unique<Database>("postgresql://postgres:password@postgres:5432/cpp_mastery_test");
        db->execute("BEGIN TRANSACTION");
    }
    
    void TearDown() override {
        // Rollback changes
        db->execute("ROLLBACK");
    }
    
    std::unique_ptr<Database> db;
};
```

## Continuous Integration

### Pre-commit Hooks
```bash
# Install pre-commit
pip install pre-commit
pre-commit install

# Run manually
pre-commit run --all-files
```

### GitHub Actions (example)
```yaml
name: CI
on: [push, pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Run tests
        run: |
          docker-compose run --rm test-runner
      - name: Generate coverage
        run: |
          docker-compose run --rm coverage
```

## Best Practices

1. **Write tests first** - Always start with failing test
2. **Small steps** - Make minimal changes to pass tests
3. **Refactor regularly** - Improve code after tests pass
4. **Test edge cases** - Boundary conditions, error cases
5. **Mock dependencies** - Isolate units under test
6. **Fast feedback** - Keep test suite running quickly
7. **Descriptive names** - Tests should document behavior

## Tools Integration

- **IDE**: VS Code with C++ TestMate extension
- **Debugging**: GDB integration in container
- **Profiling**: Valgrind, AddressSanitizer
- **Static Analysis**: clang-tidy, cppcheck
- **Formatting**: clang-format
- **Documentation**: Doxygen integration
