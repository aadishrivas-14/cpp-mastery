#!/bin/bash
# Automated linting and code quality checks

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_ROOT"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "🔍 Running C++ Code Quality Checks"
echo "=================================="

# Function to run checks
run_check() {
    local name=$1
    local command=$2
    
    echo -e "\n${YELLOW}Running $name...${NC}"
    if eval "$command"; then
        echo -e "${GREEN}✅ $name passed${NC}"
        return 0
    else
        echo -e "${RED}❌ $name failed${NC}"
        return 1
    fi
}

# Track failures
FAILED_CHECKS=0

# 1. clang-format check
if command -v clang-format &> /dev/null; then
    run_check "clang-format" \
        "find . -name '*.cpp' -o -name '*.h' -o -name '*.hpp' | grep -v build | xargs clang-format --dry-run --Werror" \
        || ((FAILED_CHECKS++))
else
    echo -e "${YELLOW}⚠️  clang-format not found, skipping${NC}"
fi

# 2. clang-tidy check
if command -v clang-tidy &> /dev/null; then
    run_check "clang-tidy" \
        "find . -name '*.cpp' | grep -v build | grep -v tests | head -20 | xargs clang-tidy --config-file=.clang-tidy -p build" \
        || ((FAILED_CHECKS++))
else
    echo -e "${YELLOW}⚠️  clang-tidy not found, skipping${NC}"
fi

# 3. cppcheck
if command -v cppcheck &> /dev/null; then
    run_check "cppcheck" \
        "cppcheck --enable=all --std=c++20 --suppress=missingIncludeSystem --error-exitcode=1 --inline-suppr \
        week-1/*/src week-2/*/src week-3/*/src week-4/*/src 2>&1 | grep -v 'Checking'" \
        || ((FAILED_CHECKS++))
else
    echo -e "${YELLOW}⚠️  cppcheck not found, skipping${NC}"
fi

# 4. Check for common issues
echo -e "\n${YELLOW}Checking for common issues...${NC}"

# Check for TODO/FIXME comments
TODO_COUNT=$(find . -name '*.cpp' -o -name '*.h' | xargs grep -n "TODO\|FIXME" | wc -l)
if [ "$TODO_COUNT" -gt 0 ]; then
    echo -e "${YELLOW}⚠️  Found $TODO_COUNT TODO/FIXME comments${NC}"
    find . -name '*.cpp' -o -name '*.h' | xargs grep -n "TODO\|FIXME" | head -5
fi

# Check for raw pointers (new/delete)
RAW_NEW=$(find . -name '*.cpp' | grep -v tests | xargs grep -n "\bnew\b" | grep -v "std::make" | wc -l)
if [ "$RAW_NEW" -gt 0 ]; then
    echo -e "${RED}❌ Found $RAW_NEW instances of raw 'new' (use smart pointers)${NC}"
    ((FAILED_CHECKS++))
fi

# Check for C-style casts
C_CASTS=$(find . -name '*.cpp' -o -name '*.h' | xargs grep -E "\([a-zA-Z_][a-zA-Z0-9_]*\s*\*?\s*\)" | grep -v "reinterpret_cast\|static_cast\|dynamic_cast\|const_cast" | wc -l)
if [ "$C_CASTS" -gt 0 ]; then
    echo -e "${YELLOW}⚠️  Found $C_CASTS potential C-style casts${NC}"
fi

# 5. Check file naming conventions
echo -e "\n${YELLOW}Checking file naming conventions...${NC}"
BAD_NAMES=$(find . -name '*.cpp' -o -name '*.h' -o -name '*.hpp' | grep -v build | grep -E "[A-Z]" | wc -l)
if [ "$BAD_NAMES" -gt 0 ]; then
    echo -e "${YELLOW}⚠️  Found $BAD_NAMES files with uppercase letters (prefer lowercase)${NC}"
fi

# 6. Check for proper header guards
echo -e "\n${YELLOW}Checking header guards...${NC}"
for header in $(find . -name '*.h' -o -name '*.hpp' | grep -v build); do
    if ! grep -q "#pragma once" "$header"; then
        echo -e "${YELLOW}⚠️  Missing #pragma once in $header${NC}"
    fi
done

# Summary
echo ""
echo "=================================="
if [ $FAILED_CHECKS -eq 0 ]; then
    echo -e "${GREEN}✅ All checks passed!${NC}"
    exit 0
else
    echo -e "${RED}❌ $FAILED_CHECKS check(s) failed${NC}"
    echo ""
    echo "To fix formatting issues:"
    echo "  find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i"
    echo ""
    echo "To run specific checks:"
    echo "  ./lint.sh format    # Auto-fix formatting"
    echo "  ./lint.sh tidy      # Run clang-tidy only"
    echo "  ./lint.sh check     # Run cppcheck only"
    exit 1
fi
