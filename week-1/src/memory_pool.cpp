#include "memory_pool.h"

MemoryPool::MemoryPool(size_t block_size, size_t block_count)
  : block_size_(block_size), block_count_(block_count) {
  // TODO: Allocate large memory block
  // TODO: Initialize free_blocks_ with pointers to each block
}

MemoryPool::~MemoryPool() {
  // TODO: Delete the allocated memory pool
}

void* MemoryPool::allocate() {
  // TODO: Return a free block if available, nullptr otherwise
  // Remove from free_blocks_ vector
  return nullptr;
}

void MemoryPool::deallocate(void* ptr) {
  // TODO: Add the block back to free_blocks_
}

size_t MemoryPool::available() const {
  // TODO: Return size of free_blocks_
  return 0;
}
