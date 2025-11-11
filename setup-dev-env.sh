#!/bin/bash
# C++ Mastery TDD Development Environment Setup

set -e

echo "🚀 Setting up C++ Mastery TDD Development Environment"

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo "❌ Docker is not installed. Please install Docker first."
    exit 1
fi

# Check if Docker Compose is installed
if ! command -v docker-compose &> /dev/null; then
    echo "❌ Docker Compose is not installed. Please install Docker Compose first."
    exit 1
fi

# Create necessary directories
echo "📁 Creating project structure..."
mkdir -p database/init
mkdir -p build
mkdir -p coverage-html

# Verify project structure
echo "✅ Verifying project structure..."
WEEK1_PROJECTS=("calculator" "banking" "smart_pointers" "memory_pool")
WEEK2_PROJECTS=("stl_benchmark" "generic_container" "expression_template" "bst_iterator" "graph_visualizer")
WEEK3_PROJECTS=("thread_pool" "lockfree_structures" "modern_cpp" "design_patterns" "hpc_library" "trading_engine")
WEEK4_PROJECTS=("http_server" "database_orm" "distributed_cache" "microservices" "realtime_comm" "monitoring")

for week in 1 2 3 4; do
    if [ ! -d "week-$week" ]; then
        echo "❌ Missing week-$week directory"
        exit 1
    fi
    
    eval "projects=(\"\${WEEK${week}_PROJECTS[@]}\")"
    for project in "${projects[@]}"; do
        if [ ! -d "week-$week/$project" ]; then
            echo "⚠️  Missing week-$week/$project directory"
        fi
    done
done

# Create database initialization script
echo "🗄️  Setting up database schema..."
cat > database/init/01-init.sql << 'EOF'
-- C++ Mastery Database Schema
CREATE DATABASE IF NOT EXISTS cpp_mastery;

\c cpp_mastery;

-- Users table for authentication examples
CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Projects table for tracking progress
CREATE TABLE IF NOT EXISTS projects (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    week INTEGER NOT NULL,
    status VARCHAR(20) DEFAULT 'not_started',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    completed_at TIMESTAMP NULL
);

-- Test results table
CREATE TABLE IF NOT EXISTS test_results (
    id SERIAL PRIMARY KEY,
    project_id INTEGER REFERENCES projects(id),
    test_name VARCHAR(100) NOT NULL,
    status VARCHAR(20) NOT NULL,
    execution_time_ms INTEGER,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Insert project data for all 21 projects
INSERT INTO projects (name, week, status) VALUES
-- Week 1
('Calculator', 1, 'not_started'),
('Banking System', 1, 'not_started'),
('Smart Pointers', 1, 'not_started'),
('Memory Pool', 1, 'not_started'),
-- Week 2
('STL Benchmark', 2, 'not_started'),
('Generic Container', 2, 'not_started'),
('Expression Template', 2, 'not_started'),
('BST Iterator', 2, 'not_started'),
('Graph Visualizer', 2, 'not_started'),
-- Week 3
('Thread Pool', 3, 'not_started'),
('Lock-Free Structures', 3, 'not_started'),
('Modern C++', 3, 'not_started'),
('Design Patterns', 3, 'not_started'),
('HPC Library', 3, 'not_started'),
('Trading Engine', 3, 'not_started'),
-- Week 4
('HTTP Server', 4, 'not_started'),
('Database ORM', 4, 'not_started'),
('Distributed Cache', 4, 'not_started'),
('Microservices', 4, 'not_started'),
('Real-time Communication', 4, 'not_started'),
('Monitoring System', 4, 'not_started');
EOF

# Install pre-commit hooks
echo "🔧 Setting up pre-commit hooks..."
if command -v pre-commit &> /dev/null; then
    pre-commit install
    echo "✅ Pre-commit hooks installed"
else
    echo "⚠️  pre-commit not found. Install with: pip install pre-commit"
fi

# Build the development environment
echo "🔨 Building development environment..."
docker-compose build cpp-dev

# Start the services
echo "🚀 Starting services..."
docker-compose up -d postgres redis

# Wait for database to be ready
echo "⏳ Waiting for database to be ready..."
sleep 10

# Run initial setup
echo "🔧 Running initial setup..."
docker-compose run --rm cpp-dev bash -c "
    echo '=== Development Environment Info ===' &&
    echo '✅ C++ Compiler:' && g++ --version | head -1 &&
    echo '✅ CMake:' && cmake --version | head -1 &&
    echo '✅ Ninja:' && ninja --version &&
    echo '✅ clang-format:' && clang-format --version | head -1 &&
    echo '✅ clang-tidy:' && clang-tidy --version | head -1 &&
    echo '✅ cppcheck:' && cppcheck --version &&
    echo '✅ Google Test:' && pkg-config --modversion gtest &&
    echo '' &&
    echo '=== Service Status ===' &&
    echo '✅ PostgreSQL:' && pg_isready -h postgres -p 5432 &&
    echo '✅ Redis:' && redis-cli -h redis ping
"

# Initialize progress tracker
echo "📊 Initializing progress tracker..."
python3 update_progress.py status

echo ""
echo "🎉 Development environment setup complete!"
echo ""
echo "📋 Project Structure:"
echo "  Week 1: 4 projects (calculator, banking, smart_pointers, memory_pool)"
echo "  Week 2: 5 projects (stl_benchmark, generic_container, expression_template, bst_iterator, graph_visualizer)"
echo "  Week 3: 6 projects (thread_pool, lockfree_structures, modern_cpp, design_patterns, hpc_library, trading_engine)"
echo "  Week 4: 6 projects (http_server, database_orm, distributed_cache, microservices, realtime_comm, monitoring)"
echo ""
echo "📋 Available commands:"
echo "  docker-compose run --rm cpp-dev                 # Enter development shell"
echo "  docker-compose run --rm test-runner             # Run all tests"
echo "  docker-compose run --rm coverage                # Generate coverage report"
echo "  docker-compose exec postgres psql -U postgres   # Access database"
echo ""
echo "🔗 Services:"
echo "  PostgreSQL: localhost:5432 (user: postgres, pass: password)"
echo "  Redis: localhost:6379"
echo ""
echo "🔧 Code Quality Tools:"
echo "  clang-format -i file.cpp                        # Format code"
echo "  clang-tidy file.cpp                             # Lint code"
echo "  cppcheck --enable=all file.cpp                  # Static analysis"
echo "  pre-commit run --all-files                      # Run all checks"
echo ""
echo "🚀 To start developing:"
echo "  docker-compose run --rm cpp-dev"
echo "  cd week-1/calculator && mkdir -p build && cd build"
echo "  cmake .. -GNinja && ninja && ctest"
echo ""
echo "📖 Read CODING_GUIDELINES.md for code standards"
echo "📖 Read HOW_TO_WORK.md for TDD workflow"
