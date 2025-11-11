#include "hash_table.h"
#include <string>

template <typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& val) {
  // TODO: Insert key-value pair
}

template <typename K, typename V>
bool HashTable<K, V>::find(const K& key, V& val) const {
  // TODO: Find value by key, return true if found
  return false;
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
  // TODO: Return number of elements
  return 0;
}

// Explicit instantiation for common types
template class HashTable<std::string, int>;
