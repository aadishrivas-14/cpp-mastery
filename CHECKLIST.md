# Development Environment Checklist

## ✅ Initial Setup (One-Time)

### System Requirements
- [ ] Docker installed and running
- [ ] Docker Compose installed
- [ ] Python 3.x installed
- [ ] Git installed

### Environment Setup
```bash
# Run setup script
./setup-dev-env.sh

# Install pre-commit
pip install pre-commit
pre-commit install

# Verify installation
docker --version
docker-compose --version
python3 --version
git --version
```

### Verify Configuration Files
- [ ] `.clang-format` exists
- [ ] `.clang-tidy` exists
- [ ] `.cppcheck` exists
- [ ] `.editorconfig` exists
- [ ] `.gitignore` exists
- [ ] `.gitattributes` exists
- [ ] `.pre-commit-config.yaml` exists
- [ ] `Makefile` exists
- [ ] `docker-compose.yml` exists

### Documentation Review
- [ ] Read `README.md` - Project overview
- [ ] Read `CODING_GUIDELINES.md` - Coding standards
- [ ] Read `LINTING_GUIDE.md` - Tool usage
- [ ] Read `HOW_TO_WORK.md` - TDD workflow
- [ ] Read `SETUP_COMPLETE.md` - Quick reference

## 🚀 Before Starting Each Project

### 1. Environment Check
```bash
# Start Docker services
make docker-up

# Verify services are running
docker-compose ps

# Check database
docker-compose exec postgres pg_isready

# Check Redis
docker-compose exec redis redis-cli ping
```

### 2. Project Navigation
```bash
# Enter development container
make docker-shell

# Navigate to project (example: calculator)
cd week-1/calculator

# Review project requirements
cat README.md
```

### 3. Test Verification
```bash
# Create build directory
mkdir -p build && cd build

# Configure with CMake
cmake .. -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
ninja

# Run tests (should fail initially - TDD Red phase)
ctest --output-on-failure
```

## 💻 During Development

### Before Writing Code
- [ ] Understand the failing test
- [ ] Read test expectations
- [ ] Plan minimal implementation

### While Writing Code
- [ ] Follow naming conventions (camelCase, snake_case, PascalCase)
- [ ] Use modern C++ features (auto, smart pointers, range-for)
- [ ] Keep functions small (< 80 lines)
- [ ] Maintain const correctness
- [ ] Use RAII for resource management

### After Writing Code
```bash
# Build
ninja

# Run tests
ctest --output-on-failure

# Format code
cd .. && clang-format -i src/*.cpp include/*.h

# Lint code
clang-tidy src/*.cpp -- -std=c++20 -Iinclude

# Check for memory leaks (if applicable)
valgrind --leak-check=full ./build/program
```

## 🔍 Before Committing

### Code Quality Checks
```bash
# Format all code
make format

# Run linters
make lint

# Run all tests
make test

# Check coverage (optional)
make coverage
```

### Manual Verification
- [ ] All tests pass
- [ ] No compiler warnings
- [ ] No linter errors
- [ ] Code formatted correctly
- [ ] No memory leaks
- [ ] Documentation updated (if needed)

### Git Workflow
```bash
# Check status
git status

# Stage changes
git add .

# Commit (pre-commit hooks run automatically)
git commit -m "feat(project): description"

# If pre-commit fails, fix issues and retry
make format
git add .
git commit -m "feat(project): description"
```

## 📊 After Completing Project

### Final Verification
- [ ] All tests pass
- [ ] Code coverage > 80%
- [ ] No linter warnings
- [ ] No memory leaks
- [ ] Documentation complete

### Update Progress
```bash
# Mark project as complete
python3 update_progress.py complete <project_name>

# Check overall progress
python3 update_progress.py status
```

### Git Workflow
```bash
# Ensure all changes committed
git status

# Push to remote (if applicable)
git push origin week-X

# Merge to main (if project complete)
git checkout main
git merge week-X
```

## 🛠️ Troubleshooting Checklist

### Docker Issues
- [ ] Docker daemon running: `docker ps`
- [ ] Services running: `docker-compose ps`
- [ ] Rebuild containers: `docker-compose build --no-cache`
- [ ] Clean up: `docker-compose down -v && docker system prune`

### Build Issues
- [ ] Clean build: `rm -rf build && mkdir build`
- [ ] CMake reconfigure: `cmake .. -GNinja`
- [ ] Check compiler: `g++ --version`
- [ ] Check CMake: `cmake --version`

### Test Issues
- [ ] Tests exist: `ls tests/`
- [ ] Tests compiled: `ls build/`
- [ ] Run verbose: `ctest --output-on-failure --verbose`
- [ ] Run specific test: `./build/test_name`

### Linting Issues
- [ ] clang-format installed: `clang-format --version`
- [ ] clang-tidy installed: `clang-tidy --version`
- [ ] Config files exist: `ls .clang-*`
- [ ] Auto-fix: `clang-tidy -fix src/*.cpp`

### Pre-commit Issues
- [ ] Installed: `pre-commit --version`
- [ ] Hooks installed: `ls .git/hooks/pre-commit`
- [ ] Reinstall: `pre-commit install`
- [ ] Run manually: `pre-commit run --all-files`

## 📋 Daily Development Routine

### Morning Startup
```bash
# 1. Start services
make docker-up

# 2. Check status
python3 update_progress.py status

# 3. Enter development environment
make docker-shell

# 4. Navigate to current project
cd week-X/project-name
```

### During Work Session
```bash
# Frequent: Build and test
ninja && ctest

# Periodic: Format and lint
make format && make lint

# Before breaks: Commit work
git add . && git commit -m "wip: description"
```

### End of Day
```bash
# 1. Final checks
make check

# 2. Commit all work
git add . && git commit -m "feat: description"

# 3. Update progress
python3 update_progress.py status

# 4. Stop services (optional)
make docker-down
```

## 🎯 Quality Standards Checklist

### Code Style
- [ ] Naming conventions followed
- [ ] 100 character line limit
- [ ] 2-space indentation
- [ ] No trailing whitespace
- [ ] LF line endings

### Modern C++
- [ ] Using `auto` where appropriate
- [ ] Using smart pointers (no raw new/delete)
- [ ] Using range-based for loops
- [ ] Using `constexpr` for constants
- [ ] Using `const` correctness
- [ ] Using uniform initialization `{}`

### Best Practices
- [ ] RAII for resource management
- [ ] Rule of Zero or Rule of Five
- [ ] No memory leaks
- [ ] No undefined behavior
- [ ] Exception safety
- [ ] Thread safety (where applicable)

### Testing
- [ ] All tests pass
- [ ] Edge cases covered
- [ ] Error cases tested
- [ ] No test warnings
- [ ] Tests are deterministic

### Documentation
- [ ] Functions documented
- [ ] Complex logic explained
- [ ] Public API documented
- [ ] README updated (if needed)

## 🔄 Weekly Review Checklist

### End of Week
- [ ] All week's projects completed
- [ ] All tests passing
- [ ] Code quality checks pass
- [ ] Progress tracker updated
- [ ] Git commits clean and descriptive
- [ ] Documentation complete

### Preparation for Next Week
- [ ] Review next week's projects
- [ ] Read theory files
- [ ] Understand requirements
- [ ] Plan approach

## 📚 Reference Quick Links

### Commands
```bash
make help           # Show all commands
make format         # Format code
make lint           # Run linters
make check          # All quality checks
make build          # Build projects
make test           # Run tests
make coverage       # Coverage report
make docker-shell   # Dev environment
```

### Documentation
- `CODING_GUIDELINES.md` - Standards
- `LINTING_GUIDE.md` - Tools
- `HOW_TO_WORK.md` - Workflow
- `CODE_QUALITY.md` - Infrastructure

### Tools
- clang-format: Format code
- clang-tidy: Lint code
- cppcheck: Static analysis
- valgrind: Memory check
- gtest: Unit testing

---

**Remember**: Quality over speed. Write clean, tested, maintainable code! 🎯
