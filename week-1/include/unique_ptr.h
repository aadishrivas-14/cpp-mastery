#pragma once

/**
 * TODO: Implement Smart Pointer (RAII Pattern)
 * 
 * Requirements:
 * - UniquePtr<T> - Owns a pointer, deletes on destruction
 * - Constructor: Takes raw pointer
 * - Destructor: Deletes owned pointer
 * - Move constructor and assignment (transfer ownership)
 * - Delete copy constructor and assignment (unique ownership)
 * - get() - Return raw pointer
 * - operator* - Dereference
 * - operator-> - Member access
 * 
 * Demonstrates:
 * - RAII (Resource Acquisition Is Initialization)
 * - Move semantics
 * - Automatic resource management
 */

template <typename T>
class UniquePtr {
 public:
  explicit UniquePtr(T* ptr = nullptr);
  ~UniquePtr();
  
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  
  UniquePtr(UniquePtr&& other) noexcept;
  
  T* get() const;
  T& operator*() const;
  T* operator->() const;
  
 private:
  T* ptr_;
};

// Template implementation
template <typename T>
UniquePtr<T>::UniquePtr(T* ptr) : ptr_(ptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
  // TODO: Delete the owned pointer
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
  // TODO: Transfer ownership (set other.ptr_ to nullptr)
}

template <typename T>
T* UniquePtr<T>::get() const {
  // TODO: Return the raw pointer
  return nullptr;
}

template <typename T>
T& UniquePtr<T>::operator*() const {
  // TODO: Dereference and return reference
  return *ptr_;
}

template <typename T>
T* UniquePtr<T>::operator->() const {
  // TODO: Return pointer for member access
  return nullptr;
}

class Resource {
 public:
  Resource();
  int getValue() const;
 private:
  int value_;
};
