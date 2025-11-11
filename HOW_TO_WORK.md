# How to Work in This Project

## 🚀 Quick Start (5 minutes)

### 1. Setup Environment (One-time)
```bash
cd /home/eshdiar/cpp/cpp-mastery
./setup-dev-env.sh
```

### 2. Start Development
```bash
# Enter development container
docker-compose run --rm cpp-dev

# Check everything works
g++ --version && cmake --version
```

## 📝 Daily TDD Workflow

### Step 1: Choose Project
```bash
cd week-1/calculator  # or any project
```

### Step 2: Write Test First (RED)
```cpp
// tests/test_calculator.cpp
TEST(CalculatorTest, AddsTwoNumbers) {
    Calculator calc;
    EXPECT_EQ(calc.add(2, 3), 5);  // This will fail initially
}
```

### Step 3: Build & See Test Fail
```bash
mkdir -p build && cd build
cmake .. -GNinja
ninja
ctest  # Should fail - RED phase
```

### Step 4: Write Minimal Code (GREEN)
```cpp
// src/calculator.cpp
int Calculator::add(int a, int b) {
    return a + b;  // Just enough to pass
}
```

### Step 5: Build & See Test Pass
```bash
ninja
ctest  # Should pass - GREEN phase
```

### Step 6: Refactor & Improve
```cpp
// Improve design, add error handling, optimize
template<typename T>
T Calculator::add(T a, T b) const noexcept {
    return a + b;
}
```

### Step 7: Track Progress
```bash
# Exit container
exit

# Update progress
python3 update_progress.py complete project "Calculator"
git add . && git commit -m "feat: implement calculator with TDD"
```

## 🔄 Repeat for Each Feature

1. **Write failing test** → RED
2. **Write minimal code** → GREEN  
3. **Refactor & improve** → REFACTOR
4. **Commit progress** → TRACK

## 📊 Useful Commands

```bash
# Run all tests
ctest --output-on-failure

# Generate coverage
docker-compose run --rm coverage

# Memory check
valgrind ./tests/test_calculator

# Static analysis
clang-tidy src/*.cpp

# Check progress
python3 update_progress.py status
```

## 📁 Project Structure
```
week-X/project-name/
├── src/           # Implementation
├── include/       # Headers  
├── tests/         # Unit tests
├── benchmarks/    # Performance tests
└── CMakeLists.txt # Build config
```

## 🎯 Focus Areas by Week

- **Week 1**: Basic C++, OOP, Memory Management
- **Week 2**: STL, Templates, Data Structures  
- **Week 3**: Concurrency, Modern C++, Performance
- **Week 4**: Networking, Databases, Systems

## 💡 Pro Tips

- **Always test first** - Write failing test before code
- **Small steps** - Make minimal changes to pass tests
- **Commit often** - Track progress with Git
- **Use containers** - Consistent environment
- **Check coverage** - Aim for >80% test coverage

**That's it!** Follow TDD cycle, track progress, and build amazing C++ projects! 🚀
