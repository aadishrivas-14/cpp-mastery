# Week 2 Projects

## Project 1: STL Algorithm Benchmark Suite
**Duration**: Day 1-2
**Skills**: STL containers, algorithms, performance analysis

### Requirements
- Benchmark sorting algorithms on different containers
- Compare search performance (linear vs binary vs hash)
- Memory usage analysis
- Visualization of results

### Files
- `benchmark.h/cpp` - Benchmarking framework
- `container_tests.cpp` - Container performance tests
- `algorithm_tests.cpp` - Algorithm performance tests
- `visualizer.cpp` - Results visualization

### Starter Code
```cpp
template<typename Container, typename Algorithm>
class Benchmark {
    std::chrono::high_resolution_clock::time_point start, end;
public:
    void run(Container& container, Algorithm algo, size_t iterations);
    double getAverageTime() const;
    void printResults() const;
};
```

## Project 2: Generic Container Library
**Duration**: Day 3-4
**Skills**: Templates, generic programming, STL compatibility

### Requirements
- Implement Vector, List, Map with STL-compatible interface
- Support for custom allocators
- Iterator implementation
- Exception safety guarantees

### Files
- `vector.h` - Dynamic array implementation
- `list.h` - Doubly-linked list
- `map.h` - Binary search tree map
- `allocator.h` - Custom allocator
- `tests.cpp` - Comprehensive test suite

### Starter Code
```cpp
template<typename T, typename Allocator = std::allocator<T>>
class Vector {
    T* data;
    size_t size_, capacity_;
    Allocator alloc;
public:
    class iterator;
    iterator begin();
    iterator end();
    void push_back(const T& value);
    void emplace_back(Args&&... args);
};
```

## Project 3: Expression Template System
**Duration**: Day 5
**Skills**: Advanced templates, metaprogramming, optimization

### Requirements
- Mathematical expression evaluation without temporaries
- Support for vectors, matrices
- Compile-time optimization
- Lazy evaluation

### Files
- `expression.h` - Expression template base
- `vector_expr.h` - Vector expressions
- `matrix_expr.h` - Matrix expressions
- `operators.h` - Operator overloads

### Starter Code
```cpp
template<typename E>
class Expression {
public:
    const E& cast() const { return static_cast<const E&>(*this); }
    auto operator[](size_t i) const { return cast()[i]; }
    size_t size() const { return cast().size(); }
};

template<typename L, typename R>
class Add : public Expression<Add<L, R>> {
    const L& left; const R& right;
public:
    Add(const L& l, const R& r) : left(l), right(r) {}
    auto operator[](size_t i) const { return left[i] + right[i]; }
};
```

## Project 4: Binary Search Tree with Iterators
**Duration**: Day 6
**Skills**: Data structures, iterator design, tree algorithms

### Requirements
- Self-balancing BST (AVL or Red-Black)
- STL-compatible iterators
- Range-based for loop support
- Tree visualization

### Files
- `bst.h` - Binary search tree implementation
- `avl_tree.h` - AVL tree balancing
- `tree_iterator.h` - Iterator implementation
- `visualizer.h` - Tree visualization

### Starter Code
```cpp
template<typename T>
class BST {
    struct Node {
        T data;
        std::unique_ptr<Node> left, right;
        int height = 1;
    };
    std::unique_ptr<Node> root;
    
public:
    class iterator {
        std::stack<Node*> stack;
    public:
        iterator& operator++();
        T& operator*();
        bool operator!=(const iterator& other);
    };
    
    iterator begin();
    iterator end();
    void insert(const T& value);
    bool find(const T& value);
};
```

## Project 5: Graph Algorithms Visualizer
**Duration**: Day 7
**Skills**: Graph algorithms, visualization, advanced data structures

### Requirements
- Graph representation (adjacency list/matrix)
- BFS, DFS, Dijkstra, A* algorithms
- Path visualization
- Performance comparison

### Files
- `graph.h` - Graph data structure
- `algorithms.h` - Graph algorithms
- `visualizer.h` - ASCII/graphical visualization
- `pathfinding.cpp` - Pathfinding demo

### Starter Code
```cpp
template<typename T>
class Graph {
    std::unordered_map<T, std::vector<std::pair<T, double>>> adj_list;
public:
    void addEdge(const T& from, const T& to, double weight = 1.0);
    std::vector<T> dijkstra(const T& start, const T& end);
    std::vector<T> aStar(const T& start, const T& end, 
                        std::function<double(const T&, const T&)> heuristic);
    void visualize() const;
};
```

## Integration Project: Algorithm Performance Analyzer
Combine all projects into a comprehensive algorithm analysis tool.

### Requirements
- Unified benchmarking framework
- Multiple data structure implementations
- Algorithm complexity verification
- Performance regression testing
- Automated report generation

## Assessment Criteria
- Template usage and generic programming
- STL compatibility and best practices
- Performance optimization
- Code organization and documentation
- Algorithm correctness and efficiency
