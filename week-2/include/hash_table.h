#pragma once
#include <map>

/**
 * TODO: Implement Hash Table
 * 
 * Requirements:
 * - insert(key, value) - Add key-value pair
 * - find(key, value) - Retrieve value by key
 * - size() - Return number of elements
 * 
 * Simplified: Use std::map as backing storage
 * Advanced: Implement with actual hash function and buckets
 */

template <typename K, typename V>
class HashTable {
 public:
  void insert(const K& key, const V& val);
  bool find(const K& key, V& val) const;
  size_t size() const;
 private:
  std::map<K, V> data_;
};
