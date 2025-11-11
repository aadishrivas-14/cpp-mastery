# Week 1 Projects

## Project 1: Expression Calculator
**Duration**: Day 1-2
**Skills**: Basic syntax, functions, parsing

Build a calculator that can parse and evaluate mathematical expressions.

### Requirements
- Support +, -, *, /, parentheses
- Handle operator precedence
- Error handling for invalid expressions
- Interactive command-line interface

### Files
- `calculator.h/cpp` - Core calculator logic
- `parser.h/cpp` - Expression parsing
- `main.cpp` - CLI interface

## Project 2: Banking System
**Duration**: Day 3-5
**Skills**: OOP, inheritance, polymorphism

Design a complete banking system with different account types.

### Requirements
- Base Account class with virtual methods
- SavingsAccount, CheckingAccount, CreditAccount
- Transaction history
- Interest calculations
- Account management system

### Files
- `account.h/cpp` - Base account class
- `savings.h/cpp` - Savings account
- `checking.h/cpp` - Checking account
- `bank.h/cpp` - Bank management
- `main.cpp` - Banking interface

## Project 3: Smart Pointer Library
**Duration**: Day 6
**Skills**: Memory management, RAII, templates

Implement your own smart pointer classes.

### Requirements
- unique_ptr equivalent
- shared_ptr with reference counting
- weak_ptr for cycle breaking
- Custom deleters support
- Thread-safe reference counting

### Files
- `unique_ptr.h` - Unique pointer implementation
- `shared_ptr.h` - Shared pointer implementation
- `weak_ptr.h` - Weak pointer implementation
- `tests.cpp` - Comprehensive tests

## Project 4: Memory Pool Allocator
**Duration**: Day 7
**Skills**: Advanced memory management

Build a high-performance memory allocator.

### Requirements
- Fixed-size block allocation
- Free list management
- Chunk-based allocation
- Performance benchmarking
- Thread-safe version

### Files
- `memory_pool.h` - Memory pool implementation
- `benchmark.cpp` - Performance tests
- `thread_safe_pool.h` - Thread-safe version

## Integration Project: Resource Manager
Combine all concepts into a comprehensive resource management system.

### Requirements
- RAII-based resource handling
- Smart pointer integration
- Memory pool for frequent allocations
- Exception-safe operations
- Performance monitoring

## Assessment Criteria
- Code quality and organization
- Proper memory management
- Exception safety
- Performance optimization
- Design pattern usage
