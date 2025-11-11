#pragma once
#include <vector>
#include <cstddef>

/**
 * TODO: Implement Memory Pool Allocator
 * 
 * Requirements:
 * - Constructor: MemoryPool(block_size, block_count)
 * - allocate() - Return pointer to free block, nullptr if exhausted
 * - deallocate(ptr) - Return block to pool
 * - available() - Return number of free blocks
 * - Destructor: Free all memory
 * 
 * Implementation hints:
 * - Allocate one large block: new char[block_size * block_count]
 * - Maintain vector of free block pointers
 * - allocate() pops from free list
 * - deallocate() pushes to free list
 * 
 * Benefits:
 * - Faster than repeated new/delete
 * - Reduces memory fragmentation
 * - Predictable allocation time
 */

class MemoryPool {
 public:
  explicit MemoryPool(size_t block_size, size_t block_count);
  ~MemoryPool();
  
  void* allocate();
  void deallocate(void* ptr);
  size_t available() const;
  
 private:
  char* pool_;
  size_t block_size_;
  size_t block_count_;
  std::vector<char*> free_blocks_;
};
