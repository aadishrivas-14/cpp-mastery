#pragma once

#include <string>
#include <optional>

/**
 * TODO: Implement a Distributed Cache
 * 
 * Requirements:
 * - set(key, value, ttl) - Store with expiration
 * - get(key) - Retrieve value
 * - remove(key) - Delete value
 * - clear() - Clear all
 * 
 * Features:
 * - TTL (Time To Live) support
 * - LRU eviction policy
 * - Thread-safe operations
 * 
 * Implementation hints:
 * - Use std::map for storage
 * - Use std::chrono for TTL
 * - Use std::mutex for thread safety
 */

// TODO: Implement DistributedCache class
