# Memory Management & RAII

## Stack vs Heap
```cpp
void stackExample() {
    int x = 42;           // Stack allocation
    char buffer[1024];    // Stack allocation
}  // Automatically destroyed

void heapExample() {
    int* ptr = new int(42);     // Heap allocation
    int* arr = new int[1000];   // Heap array
    
    delete ptr;     // Manual cleanup required
    delete[] arr;   // Array deletion
}
```

## RAII (Resource Acquisition Is Initialization)
```cpp
class FileHandler {
private:
    std::FILE* file;
    
public:
    FileHandler(const char* filename, const char* mode) 
        : file(std::fopen(filename, mode)) {
        if (!file) {
            throw std::runtime_error("Cannot open file");
        }
    }
    
    ~FileHandler() {
        if (file) {
            std::fclose(file);
        }
    }
    
    // Disable copy to prevent double deletion
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;
    
    // Enable move
    FileHandler(FileHandler&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }
    
    std::FILE* get() const { return file; }
};
```

## Smart Pointers
```cpp
#include <memory>

// unique_ptr - Exclusive ownership
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = std::move(ptr1);  // Transfer ownership

// shared_ptr - Shared ownership
std::shared_ptr<int> sptr1 = std::make_shared<int>(42);
std::shared_ptr<int> sptr2 = sptr1;  // Reference count = 2

// weak_ptr - Non-owning observer
std::weak_ptr<int> wptr = sptr1;
if (auto locked = wptr.lock()) {
    // Use locked safely
}

// Custom deleter
auto custom_deleter = [](int* p) {
    std::cout << "Deleting " << *p << std::endl;
    delete p;
};
std::unique_ptr<int, decltype(custom_deleter)> ptr(new int(42), custom_deleter);
```

## Rule of Three/Five/Zero
```cpp
class Resource {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    Resource(size_t s) : size(s), data(new int[s]) {}
    
    // Destructor
    ~Resource() { delete[] data; }
    
    // Copy constructor
    Resource(const Resource& other) : size(other.size), data(new int[size]) {
        std::copy(other.data, other.data + size, data);
    }
    
    // Copy assignment
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    // Move constructor (C++11)
    Resource(Resource&& other) noexcept : size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment (C++11)
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
```

## Memory Pool Allocator
```cpp
template<typename T, size_t BlockSize = 4096>
class MemoryPool {
private:
    struct Block {
        alignas(T) char data[sizeof(T)];
        Block* next;
    };
    
    Block* freeList;
    std::vector<std::unique_ptr<Block[]>> chunks;
    
public:
    MemoryPool() : freeList(nullptr) {
        allocateChunk();
    }
    
    T* allocate() {
        if (!freeList) {
            allocateChunk();
        }
        Block* block = freeList;
        freeList = freeList->next;
        return reinterpret_cast<T*>(block);
    }
    
    void deallocate(T* ptr) {
        Block* block = reinterpret_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }
    
private:
    void allocateChunk() {
        auto chunk = std::make_unique<Block[]>(BlockSize);
        for (size_t i = 0; i < BlockSize - 1; ++i) {
            chunk[i].next = &chunk[i + 1];
        }
        chunk[BlockSize - 1].next = freeList;
        freeList = chunk.get();
        chunks.push_back(std::move(chunk));
    }
};
```
