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
