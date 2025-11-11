# Standard Template Library

## Containers Overview
```cpp
// Sequence containers
std::vector<int> vec = {1, 2, 3, 4, 5};        // Dynamic array
std::deque<int> dq;                             // Double-ended queue
std::list<int> lst;                             // Doubly-linked list
std::array<int, 5> arr = {1, 2, 3, 4, 5};     // Fixed-size array

// Associative containers
std::set<int> s = {3, 1, 4, 1, 5};             // Sorted unique elements
std::map<string, int> m = {{"a", 1}, {"b", 2}}; // Key-value pairs
std::multiset<int> ms;                          // Sorted with duplicates
std::multimap<string, int> mm;                  // Multiple values per key

// Unordered containers (hash tables)
std::unordered_set<int> us;                     // Hash set
std::unordered_map<string, int> um;             // Hash map

// Container adapters
std::stack<int> stk;                            // LIFO
std::queue<int> q;                              // FIFO
std::priority_queue<int> pq;                    // Max heap
```

## Algorithms
```cpp
#include <algorithm>
#include <numeric>

std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};

// Sorting
std::sort(vec.begin(), vec.end());
std::partial_sort(vec.begin(), vec.begin() + 3, vec.end());
std::nth_element(vec.begin(), vec.begin() + 4, vec.end());

// Searching
auto it = std::find(vec.begin(), vec.end(), 5);
auto it2 = std::find_if(vec.begin(), vec.end(), [](int x) { return x > 5; });
bool found = std::binary_search(vec.begin(), vec.end(), 4);

// Transforming
std::vector<int> squares(vec.size());
std::transform(vec.begin(), vec.end(), squares.begin(), 
               [](int x) { return x * x; });

// Numeric algorithms
int sum = std::accumulate(vec.begin(), vec.end(), 0);
int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());

// Parallel algorithms (C++17)
std::sort(std::execution::par, vec.begin(), vec.end());
```

## Custom Iterators
```cpp
template<typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    size_t head, tail, count;
    
public:
    class iterator {
        CircularBuffer* buf;
        size_t pos;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator(CircularBuffer* b, size_t p) : buf(b), pos(p) {}
        
        reference operator*() { return buf->buffer[pos]; }
        pointer operator->() { return &buf->buffer[pos]; }
        
        iterator& operator++() {
            pos = (pos + 1) % buf->buffer.size();
            return *this;
        }
        
        bool operator==(const iterator& other) const {
            return buf == other.buf && pos == other.pos;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };
    
    iterator begin() { return iterator(this, head); }
    iterator end() { return iterator(this, (head + count) % buffer.size()); }
};
```

## Performance Characteristics
| Container | Access | Insert | Delete | Search |
|-----------|--------|--------|--------|--------|
| vector | O(1) | O(n) | O(n) | O(n) |
| deque | O(1) | O(1) ends | O(1) ends | O(n) |
| list | O(n) | O(1) | O(1) | O(n) |
| set | O(log n) | O(log n) | O(log n) | O(log n) |
| unordered_set | O(1) avg | O(1) avg | O(1) avg | O(1) avg |
