# Code Quality Infrastructure

## Overview
This project has a comprehensive code quality infrastructure to ensure consistent, maintainable, and bug-free C++ code.

## Configuration Files

### Formatting and Style
- **`.clang-format`** - Code formatting rules (Google style, 100 char limit, 2-space indent)
- **`.editorconfig`** - Editor-agnostic formatting settings
- **`.gitattributes`** - Consistent line endings (LF) across platforms

### Static Analysis
- **`.clang-tidy`** - Static analysis and linting rules
- **`.cppcheck`** - Additional static analysis configuration

### Automation
- **`.pre-commit-config.yaml`** - Pre-commit hooks for automated checks
- **`Makefile`** - Common development tasks
- **`setup-dev-env.sh`** - Environment setup script

### Version Control
- **`.gitignore`** - Files to exclude from Git

## Tools Stack

### 1. Code Formatting
- **clang-format** - Automatic code formatting
  - Based on Google C++ Style Guide
  - 100 character line limit
  - 2-space indentation
  - Consistent pointer/reference alignment

### 2. Static Analysis
- **clang-tidy** - Comprehensive linting
  - Naming convention enforcement
  - Modern C++ feature suggestions
  - Performance optimizations
  - Bug detection
  
- **cppcheck** - Additional static analysis
  - Memory leak detection
  - Null pointer dereferences
  - Buffer overflows
  - Uninitialized variables

### 3. Runtime Analysis
- **AddressSanitizer (ASan)** - Memory error detection
  - Use-after-free
  - Buffer overflows
  - Memory leaks
  
- **Valgrind** - Memory debugging
  - Detailed leak detection
  - Invalid memory access
  - Uninitialized values

### 4. Testing
- **Google Test** - Unit testing framework
- **Google Mock** - Mocking framework
- **Coverage tools** - Code coverage analysis

### 5. Automation
- **pre-commit** - Git hooks for automated checks
- **Make** - Build and quality task automation
- **Docker** - Consistent development environment

## Quick Commands

### Setup
```bash
# Initial setup
./setup-dev-env.sh

# Install pre-commit hooks
pre-commit install
```

### Development
```bash
# Format all code
make format

# Run linters
make lint

# Run all quality checks
make check

# Build projects
make build

# Run tests
make test

# Generate coverage
make coverage
```

### Docker
```bash
# Start services
make docker-up

# Enter development shell
make docker-shell

# Stop services
make docker-down
```

### Manual Checks
```bash
# Format single file
clang-format -i src/file.cpp

# Lint single file
clang-tidy src/file.cpp -- -std=c++20 -Iinclude

# Static analysis
cppcheck --enable=all src/

# Memory check
valgrind --leak-check=full ./program

# Address sanitizer
g++ -fsanitize=address -g src/file.cpp -o program
```

## Naming Conventions

### Classes and Structs
```cpp
class BankAccount {};      // PascalCase
struct TreeNode {};        // PascalCase
```

### Functions and Methods
```cpp
void calculateBalance();   // camelCase
int getAccountNumber();    // camelCase
```

### Variables
```cpp
int account_balance;       // snake_case
std::string user_name;     // snake_case
```

### Constants
```cpp
const int MAX_SIZE = 100;  // UPPER_SNAKE_CASE
constexpr double PI = 3.14;
```

### Private/Protected Members
```cpp
class Account {
 private:
  int balance_;            // Suffix with underscore
  std::string name_;
};
```

### Namespaces
```cpp
namespace banking_system {}  // snake_case
```

## Workflow

### Before Every Commit
1. **Format code**: `make format`
2. **Run linters**: `make lint`
3. **Build**: `make build`
4. **Test**: `make test`
5. **Commit**: `git commit`

Pre-commit hooks will automatically:
- Format code with clang-format
- Run clang-tidy checks
- Remove trailing whitespace
- Fix line endings
- Validate YAML/JSON files

### During Development
```bash
# Enter development container
docker-compose run --rm cpp-dev

# Navigate to project
cd week-1/calculator

# Create build directory
mkdir -p build && cd build

# Configure with CMake
cmake .. -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
ninja

# Run tests
ctest --output-on-failure

# Run with sanitizers
cmake .. -DCMAKE_CXX_FLAGS="-fsanitize=address -g"
ninja && ./calculator
```

### Code Review Checklist
- [ ] Code formatted with clang-format
- [ ] No clang-tidy warnings
- [ ] No cppcheck warnings
- [ ] All tests pass
- [ ] No memory leaks (Valgrind)
- [ ] No sanitizer errors (ASan)
- [ ] Code coverage > 80%
- [ ] Documentation updated
- [ ] Commit message follows convention

## Continuous Integration

### Local CI Simulation
```bash
# Run full CI pipeline locally
./ci-local.sh

# Or manually:
make format
make lint
make build
make test
make coverage
```

### CI Checks (Automated)
1. Code formatting verification
2. Static analysis (clang-tidy, cppcheck)
3. Build all projects
4. Run all tests
5. Generate coverage report
6. Memory leak detection
7. Sanitizer checks

## Suppressing Warnings

### When to Suppress
- False positives
- Third-party code
- Intentional design decisions
- Performance-critical code

### How to Suppress
```cpp
// Suppress all warnings on this line
int value = 42;  // NOLINT

// Suppress specific check
// NOLINTNEXTLINE(modernize-use-auto)
std::vector<int>::iterator it = vec.begin();

// Suppress in block
// NOLINTBEGIN(readability-magic-numbers)
int array[] = {1, 2, 3, 4, 5};
// NOLINTEND(readability-magic-numbers)
```

## Editor Integration

### VSCode
1. Install extensions:
   - C/C++ (Microsoft)
   - clangd
   - C/C++ Advanced Lint

2. Settings (`.vscode/settings.json`):
```json
{
  "C_Cpp.clang_format_style": "file",
  "editor.formatOnSave": true,
  "clangd.arguments": ["--clang-tidy"]
}
```

### Vim/Neovim
```vim
" Format on save
autocmd BufWritePre *.cpp,*.h :silent! %!clang-format
```

### CLion
- Settings → Editor → Code Style → C/C++
- Enable ClangFormat
- Use `.clang-format` file

## Troubleshooting

### clang-format not found
```bash
# Ubuntu/Debian
sudo apt install clang-format

# macOS
brew install clang-format
```

### clang-tidy not found
```bash
# Ubuntu/Debian
sudo apt install clang-tidy

# macOS
brew install llvm
```

### pre-commit not found
```bash
pip install pre-commit
pre-commit install
```

### Docker issues
```bash
# Rebuild containers
docker-compose build --no-cache

# Clean up
docker-compose down -v
docker system prune -a
```

## Performance Optimization

### Speed Up Linting
```bash
# Use compilation database
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# Parallel linting
find . -name "*.cpp" | xargs -P $(nproc) -I {} clang-tidy {}
```

### Speed Up Builds
```bash
# Use Ninja instead of Make
cmake .. -GNinja

# Parallel builds
ninja -j $(nproc)
```

### Cache Results
```bash
# cppcheck cache
cppcheck --cppcheck-build-dir=.cppcheck-cache src/

# ccache for compilation
export CC="ccache gcc"
export CXX="ccache g++"
```

## Documentation

- **`CODING_GUIDELINES.md`** - Comprehensive coding standards
- **`LINTING_GUIDE.md`** - Detailed linting tool usage
- **`HOW_TO_WORK.md`** - TDD workflow and project structure
- **`README.md`** - Project overview

## Resources

### Official Documentation
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [cppcheck](http://cppcheck.sourceforge.net/)
- [Google Test](https://google.github.io/googletest/)

### Style Guides
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

### Learning Resources
- [Modern C++ Best Practices](https://github.com/cpp-best-practices/cppbestpractices)
- [Awesome Modern C++](https://github.com/rigtorp/awesome-modern-cpp)

## Metrics

### Code Quality Targets
- **Test Coverage**: > 80%
- **Cyclomatic Complexity**: < 10 per function
- **Function Length**: < 80 lines
- **File Length**: < 500 lines
- **Parameter Count**: < 5 per function
- **Nesting Depth**: < 4 levels

### Monitoring
```bash
# Check coverage
make coverage
open coverage-html/index.html

# Check complexity
lizard src/ --CCN 10

# Check metrics
cloc src/
```

## Support

For issues or questions:
1. Check documentation in `docs/`
2. Review `CODING_GUIDELINES.md`
3. Consult `LINTING_GUIDE.md`
4. Check tool documentation links above
