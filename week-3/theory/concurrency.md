# Multithreading & Concurrency

## Basic Threading
```cpp
#include <thread>
#include <mutex>
#include <condition_variable>

// Creating threads
void worker_function(int id) {
    std::cout << "Worker " << id << " running\n";
}

std::thread t1(worker_function, 1);
std::thread t2([]() { std::cout << "Lambda thread\n"; });

t1.join();  // Wait for completion
t2.join();

// Thread with return value
std::future<int> future = std::async(std::launch::async, []() {
    return 42;
});
int result = future.get();
```

## Synchronization Primitives
```cpp
// Mutex for mutual exclusion
std::mutex mtx;
int shared_data = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data;
}

// Condition variables
std::condition_variable cv;
std::mutex cv_mtx;
bool ready = false;

void producer() {
    {
        std::lock_guard<std::mutex> lock(cv_mtx);
        ready = true;
    }
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(cv_mtx);
    cv.wait(lock, []{ return ready; });
    // Process data
}
```

## Atomic Operations
```cpp
#include <atomic>

std::atomic<int> counter{0};
std::atomic<bool> flag{false};

// Lock-free increment
counter.fetch_add(1);

// Compare and swap
int expected = 5;
bool success = counter.compare_exchange_weak(expected, 10);

// Memory ordering
counter.store(42, std::memory_order_release);
int value = counter.load(std::memory_order_acquire);
```

## Thread Pool
```cpp
class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
    
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this]{ return stop || !tasks.empty(); });
                        
                        if (stop && tasks.empty()) return;
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return res;
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker: workers) {
            worker.join();
        }
    }
};
```

## Lock-Free Data Structures
```cpp
template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::atomic<T*> data;
        std::atomic<Node*> next;
        Node() : data(nullptr), next(nullptr) {}
    };
    
    std::atomic<Node*> head;
    std::atomic<Node*> tail;
    
public:
    LockFreeQueue() {
        Node* dummy = new Node;
        head.store(dummy);
        tail.store(dummy);
    }
    
    void enqueue(T item) {
        Node* new_node = new Node;
        T* data = new T(std::move(item));
        new_node->data.store(data);
        
        Node* prev_tail = tail.exchange(new_node);
        prev_tail->next.store(new_node);
    }
    
    bool dequeue(T& result) {
        Node* head_node = head.load();
        Node* next = head_node->next.load();
        
        if (next == nullptr) {
            return false;  // Queue is empty
        }
        
        T* data = next->data.load();
        if (data == nullptr) {
            return false;
        }
        
        result = *data;
        head.store(next);
        delete data;
        delete head_node;
        return true;
    }
};
```
