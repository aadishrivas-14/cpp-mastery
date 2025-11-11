# Week 3 Projects

## Project 1: Thread Pool with Work Stealing
**Duration**: Day 1-2
**Skills**: Multithreading, work stealing, task scheduling

### Requirements
- Thread pool with configurable worker count
- Work stealing queue implementation
- Task priority support
- Future/promise integration
- Performance monitoring

### Files
- `thread_pool.h/cpp` - Main thread pool class
- `work_stealing_queue.h` - Lock-free work stealing queue
- `task.h` - Task wrapper with priorities
- `scheduler.cpp` - Task scheduling demo

### Starter Code
```cpp
class ThreadPool {
    std::vector<std::thread> workers;
    std::vector<WorkStealingQueue<Task>> queues;
    std::atomic<bool> shutdown{false};
    
public:
    ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
    
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<std::result_of_t<F(Args...)>>;
    
    void wait_for_all();
    ~ThreadPool();
};

template<typename T>
class WorkStealingQueue {
    std::deque<T> queue;
    mutable std::mutex mutex;
public:
    void push(T item);
    bool try_pop(T& item);
    bool try_steal(T& item);
};
```

## Project 2: Lock-Free Data Structures
**Duration**: Day 3
**Skills**: Atomic operations, memory ordering, lock-free programming

### Requirements
- Lock-free stack and queue
- ABA problem handling
- Memory reclamation (hazard pointers)
- Performance comparison with locked versions

### Files
- `lock_free_stack.h` - Lock-free stack implementation
- `lock_free_queue.h` - Lock-free queue implementation
- `hazard_pointers.h` - Memory reclamation
- `performance_test.cpp` - Benchmarking

### Starter Code
```cpp
template<typename T>
class LockFreeStack {
    struct Node {
        T data;
        std::atomic<Node*> next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    std::atomic<Node*> head{nullptr};
    
public:
    void push(const T& data);
    bool pop(T& result);
    bool empty() const;
};

template<typename T>
class LockFreeQueue {
    struct Node {
        std::atomic<T*> data{nullptr};
        std::atomic<Node*> next{nullptr};
    };
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    
public:
    void enqueue(T item);
    bool dequeue(T& result);
};
```

## Project 3: Modern C++ Feature Showcase
**Duration**: Day 4
**Skills**: C++17/20 features, concepts, ranges, coroutines

### Requirements
- Concepts for type constraints
- Ranges and views usage
- Coroutines for async operations
- std::optional, std::variant usage
- Module system (if supported)

### Files
- `concepts_demo.cpp` - Custom concepts implementation
- `ranges_demo.cpp` - Ranges and views examples
- `coroutines_demo.cpp` - Coroutine-based async I/O
- `modern_features.cpp` - C++17/20 feature showcase

### Starter Code
```cpp
// Concepts
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T add(T a, T b) { return a + b; }

// Coroutines
#include <coroutine>
struct Task {
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    Task(std::coroutine_handle<promise_type> h) : coro(h) {}
};

Task async_operation();
```

## Project 4: Design Pattern Framework
**Duration**: Day 5
**Skills**: Design patterns, template metaprogramming, policy-based design

### Requirements
- Factory pattern with registration
- Observer pattern with type safety
- Strategy pattern with policies
- Command pattern with undo/redo
- Visitor pattern for AST traversal

### Files
- `factory.h` - Generic factory implementation
- `observer.h` - Type-safe observer pattern
- `strategy.h` - Policy-based strategy pattern
- `command.h` - Command pattern with history
- `visitor.h` - Visitor pattern for AST

### Starter Code
```cpp
// Factory Pattern
template<typename Base, typename Key = std::string>
class Factory {
    std::unordered_map<Key, std::function<std::unique_ptr<Base>()>> creators;
    
public:
    template<typename Derived>
    void register_type(const Key& key) {
        creators[key] = []() { return std::make_unique<Derived>(); };
    }
    
    std::unique_ptr<Base> create(const Key& key);
};

// Observer Pattern
template<typename Event>
class Observable {
    std::vector<std::function<void(const Event&)>> observers;
    
public:
    void subscribe(std::function<void(const Event&)> observer);
    void notify(const Event& event);
};
```

## Project 5: High-Performance Computing Library
**Duration**: Day 6
**Skills**: SIMD, vectorization, cache optimization, parallel algorithms

### Requirements
- SIMD-optimized mathematical operations
- Parallel algorithms implementation
- Cache-friendly data structures
- Memory pool allocators
- Performance profiling tools

### Files
- `simd_math.h` - SIMD mathematical operations
- `parallel_algorithms.h` - Parallel STL-like algorithms
- `cache_friendly.h` - Cache-optimized data structures
- `profiler.h` - Performance profiling utilities

### Starter Code
```cpp
#include <immintrin.h>

class SIMDMath {
public:
    static void vector_add_avx(const float* a, const float* b, float* result, size_t size);
    static void matrix_multiply_simd(const float* a, const float* b, float* c, 
                                   size_t rows, size_t cols, size_t inner);
    static float dot_product_avx(const float* a, const float* b, size_t size);
};

template<typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function f) {
    const size_t num_threads = std::thread::hardware_concurrency();
    const size_t chunk_size = std::distance(first, last) / num_threads;
    
    std::vector<std::thread> threads;
    // Implementation...
}
```

## Project 6: Real-Time Trading Engine
**Duration**: Day 7
**Skills**: Low-latency programming, order matching, market data processing

### Requirements
- Order book implementation
- Market data feed processing
- Order matching engine
- Risk management system
- Latency measurement and optimization

### Files
- `order_book.h` - Limit order book
- `market_data.h` - Market data processing
- `matching_engine.h` - Order matching logic
- `risk_manager.h` - Risk management
- `latency_monitor.h` - Performance monitoring

### Starter Code
```cpp
struct Order {
    uint64_t id;
    char side; // 'B' or 'S'
    double price;
    uint64_t quantity;
    std::chrono::nanoseconds timestamp;
};

class OrderBook {
    std::map<double, uint64_t> bids;  // price -> total quantity
    std::map<double, uint64_t> asks;
    std::unordered_map<uint64_t, Order> orders; // id -> order
    
public:
    void add_order(const Order& order);
    void cancel_order(uint64_t order_id);
    std::vector<Trade> match_orders();
    void print_book(int levels = 5) const;
};

class MatchingEngine {
    OrderBook book;
    std::vector<Trade> trades;
    
public:
    void process_order(const Order& order);
    std::vector<Trade> get_trades();
    void clear_trades();
};
```

## Integration Project: Multi-threaded Application Framework
Combine all concepts into a high-performance application framework.

### Requirements
- Thread pool with work stealing
- Lock-free message passing
- Modern C++ API design
- Performance monitoring
- Real-world application (trading system, game engine, etc.)

## Assessment Criteria
- Concurrent programming correctness
- Performance optimization techniques
- Modern C++ feature usage
- Design pattern implementation
- System architecture and scalability
