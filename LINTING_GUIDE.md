# Linting and Code Quality Guide

## Overview
This project uses multiple tools to ensure code quality, consistency, and correctness. All code must pass these checks before being committed.

## Tools

### 1. clang-format (Code Formatting)
Automatically formats code according to `.clang-format` configuration.

**Usage:**
```bash
# Format a single file
clang-format -i src/calculator.cpp

# Format all C++ files
find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Check formatting without modifying
clang-format --dry-run --Werror src/calculator.cpp

# Using Make
make format
```

**Configuration:** `.clang-format`
- Based on Google style
- 100 character line limit
- 2-space indentation
- Pointer alignment left

### 2. clang-tidy (Static Analysis)
Performs static analysis and suggests improvements.

**Usage:**
```bash
# Analyze a single file
clang-tidy src/calculator.cpp -- -std=c++20 -Iinclude

# Analyze with fixes
clang-tidy -fix src/calculator.cpp -- -std=c++20 -Iinclude

# Analyze all files
find . -name "*.cpp" | xargs -I {} clang-tidy {} -- -std=c++20 -Iinclude

# Using Make
make lint
```

**Configuration:** `.clang-tidy`
- Enables most checks except platform-specific ones
- Enforces naming conventions
- Treats most warnings as errors
- Checks for modern C++ usage

**Common Issues:**
- `readability-identifier-naming`: Fix naming conventions
- `modernize-*`: Use modern C++ features
- `performance-*`: Performance improvements
- `bugprone-*`: Potential bugs

### 3. cppcheck (Additional Static Analysis)
Complementary static analysis tool.

**Usage:**
```bash
# Check a single file
cppcheck --enable=all --suppress=missingInclude src/calculator.cpp

# Check entire project
cppcheck --enable=all --suppress=missingInclude --project=compile_commands.json

# Check with specific standard
cppcheck --std=c++20 --enable=all src/

# Using configuration file
cppcheck --project=compile_commands.json
```

**Configuration:** `.cppcheck`
- Enables all checks
- Suppresses missing include warnings
- C++20 standard
- Exhaustive checking

### 4. AddressSanitizer (Runtime Checks)
Detects memory errors at runtime.

**Usage:**
```bash
# Compile with ASan
g++ -fsanitize=address -g src/calculator.cpp -o calculator

# Run with ASan
./calculator

# With CMake
cmake -DCMAKE_CXX_FLAGS="-fsanitize=address -g" ..
```

**Detects:**
- Use after free
- Heap buffer overflow
- Stack buffer overflow
- Memory leaks
- Use after return

### 5. Valgrind (Memory Leak Detection)
Comprehensive memory debugging tool.

**Usage:**
```bash
# Basic memory check
valgrind --leak-check=full ./calculator

# Detailed check
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./calculator

# Generate suppression file
valgrind --leak-check=full --gen-suppressions=all ./calculator
```

**Checks:**
- Memory leaks
- Invalid memory access
- Uninitialized values
- Double free

### 6. pre-commit (Automated Checks)
Runs checks automatically before commits.

**Setup:**
```bash
# Install pre-commit
pip install pre-commit

# Install hooks
pre-commit install

# Run manually
pre-commit run --all-files
```

**Configuration:** `.pre-commit-config.yaml`
- Runs clang-format
- Runs clang-tidy
- Checks trailing whitespace
- Checks YAML syntax
- Formats CMake files

## Workflow

### Before Committing
```bash
# 1. Format code
make format

# 2. Run linters
make lint

# 3. Run all checks
make check

# 4. Build and test
make build test

# 5. Commit
git add .
git commit -m "feat: add calculator"
```

### Continuous Integration
Pre-commit hooks automatically run:
1. clang-format (formatting)
2. clang-tidy (static analysis)
3. Trailing whitespace removal
4. End-of-file fixer
5. YAML validation

### Manual Deep Check
```bash
# Full static analysis
clang-tidy src/*.cpp -- -std=c++20 -Iinclude

# Memory check
valgrind --leak-check=full ./build/program

# Address sanitizer
cmake -DCMAKE_CXX_FLAGS="-fsanitize=address" .. && make && ./program

# Coverage
make coverage
```

## Common Issues and Fixes

### Issue: "readability-identifier-naming"
**Problem:** Incorrect naming convention
```cpp
// Bad
class bank_account {};  // Should be BankAccount
void ProcessData();     // Should be processData
int MaxValue;           // Should be MAX_VALUE or max_value
```

**Fix:**
```cpp
// Good
class BankAccount {};
void processData();
const int MAX_VALUE = 100;
int max_value = 50;
```

### Issue: "modernize-use-auto"
**Problem:** Not using auto for type deduction
```cpp
// Bad
std::vector<int>::iterator it = vec.begin();
```

**Fix:**
```cpp
// Good
auto it = vec.begin();
```

### Issue: "modernize-use-nullptr"
**Problem:** Using NULL instead of nullptr
```cpp
// Bad
int* ptr = NULL;
```

**Fix:**
```cpp
// Good
int* ptr = nullptr;
```

### Issue: "performance-unnecessary-copy-initialization"
**Problem:** Unnecessary copy
```cpp
// Bad
auto item = container[i];  // Copies the item
```

**Fix:**
```cpp
// Good
const auto& item = container[i];  // Reference, no copy
```

### Issue: "cppcoreguidelines-pro-type-member-init"
**Problem:** Uninitialized member variables
```cpp
// Bad
class Account {
  int balance;  // Uninitialized
};
```

**Fix:**
```cpp
// Good
class Account {
  int balance_{0};  // Initialized
};
```

### Issue: "bugprone-use-after-move"
**Problem:** Using object after std::move
```cpp
// Bad
auto data = std::move(original);
process(original);  // original is in moved-from state
```

**Fix:**
```cpp
// Good
auto data = std::move(original);
process(data);  // Use the new object
```

## Suppressing Warnings

### In Code (Use Sparingly)
```cpp
// NOLINT - Suppress all warnings on this line
int value = 42;  // NOLINT

// NOLINTNEXTLINE - Suppress warnings on next line
// NOLINTNEXTLINE(readability-identifier-naming)
int MyVariable = 42;

// Suppress specific check
// NOLINT(modernize-use-auto)
std::vector<int>::iterator it = vec.begin();
```

### In Configuration
Add to `.clang-tidy`:
```yaml
Checks: >
  *,
  -specific-check-to-disable
```

## Editor Integration

### VSCode
Install extensions:
- C/C++ (Microsoft)
- clangd
- C/C++ Advanced Lint

Settings (`.vscode/settings.json`):
```json
{
  "C_Cpp.clang_format_style": "file",
  "editor.formatOnSave": true,
  "clangd.arguments": ["--clang-tidy"]
}
```

### Vim/Neovim
```vim
" Use clang-format
autocmd FileType cpp setlocal formatprg=clang-format

" Format on save
autocmd BufWritePre *.cpp,*.h :silent! %!clang-format
```

### CLion
Settings → Editor → Code Style → C/C++
- Enable ClangFormat
- Use `.clang-format` file

## Performance Tips

### Speed Up clang-tidy
```bash
# Use compilation database
clang-tidy --use-color --export-fixes=fixes.yaml src/file.cpp

# Parallel execution
find . -name "*.cpp" | xargs -P $(nproc) -I {} clang-tidy {}
```

### Speed Up cppcheck
```bash
# Use multiple threads
cppcheck -j $(nproc) src/

# Cache results
cppcheck --cppcheck-build-dir=.cppcheck-cache src/
```

## CI/CD Integration

### GitHub Actions
```yaml
- name: Run clang-format
  run: |
    find . -name "*.cpp" -o -name "*.h" | xargs clang-format --dry-run --Werror

- name: Run clang-tidy
  run: |
    clang-tidy src/*.cpp -- -std=c++20

- name: Run tests with ASan
  run: |
    cmake -DCMAKE_CXX_FLAGS="-fsanitize=address" ..
    make && ctest
```

## Resources
- [clang-format documentation](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-tidy checks](https://clang.llvm.org/extra/clang-tidy/checks/list.html)
- [cppcheck manual](http://cppcheck.sourceforge.net/manual.pdf)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
