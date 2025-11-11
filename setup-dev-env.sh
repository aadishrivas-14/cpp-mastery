#!/bin/bash
# C++ Mastery Development Environment Setup

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
mkdir -p {week-1,week-2,week-3,week-4}/{src,include,tests,benchmarks}
mkdir -p database/init
mkdir -p build
mkdir -p coverage-html

# Create database initialization script
cat > database/init/01-init.sql << 'EOF'
-- C++ Mastery Database Schema
CREATE DATABASE IF NOT EXISTS cpp_mastery;

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

-- Insert sample data
INSERT INTO projects (name, week, status) VALUES
('Calculator', 1, 'not_started'),
('Banking System', 1, 'not_started'),
('Smart Pointers', 1, 'not_started'),
('STL Benchmark', 2, 'not_started'),
('Thread Pool', 3, 'not_started'),
('HTTP Server', 4, 'not_started');
EOF

# Create example test configuration
cat > .clang-tidy << 'EOF'
Checks: >
  *,
  -abseil-*,
  -altera-*,
  -android-*,
  -fuchsia-*,
  -google-*,
  -llvm-*,
  -zircon-*,
  -readability-magic-numbers,
  -cppcoreguidelines-avoid-magic-numbers,
  -modernize-use-trailing-return-type
WarningsAsErrors: ''
HeaderFilterRegex: '.*'
FormatStyle: none
EOF

# Create pre-commit configuration
cat > .pre-commit-config.yaml << 'EOF'
repos:
  - repo: local
    hooks:
      - id: cpp-tests
        name: C++ Tests
        entry: docker-compose run --rm test-runner
        language: system
        files: \.(cpp|h|hpp)$
        pass_filenames: false
      - id: clang-format
        name: clang-format
        entry: clang-format
        language: system
        files: \.(cpp|h|hpp)$
        args: ['-i']
EOF

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
    echo '✅ C++ Compiler version:' && g++ --version | head -1
    echo '✅ CMake version:' && cmake --version | head -1
    echo '✅ Testing framework:' && pkg-config --modversion gtest
    echo '✅ Database connection:' && pg_isready -h postgres -p 5432
    echo '✅ Redis connection:' && redis-cli -h redis ping
"

echo "🎉 Development environment setup complete!"
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
echo "🚀 To start developing:"
echo "  docker-compose run --rm cpp-dev"
echo "  cd week-1 && mkdir -p build && cd build"
echo "  cmake .. -GNinja && ninja && ctest"
