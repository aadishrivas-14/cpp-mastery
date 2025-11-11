#pragma once
#include <vector>
#include <map>

/**
 * TODO: Implement Graph Data Structure
 * 
 * Requirements:
 * - addEdge(u, v) - Add directed edge from u to v
 * - getNeighbors(u) - Return list of neighbors
 * 
 * Representation: Adjacency list using std::map
 * 
 * Advanced (optional):
 * - Implement BFS/DFS traversal
 * - Find shortest path
 */

class Graph {
 public:
  void addEdge(int u, int v);
  const std::vector<int>& getNeighbors(int u) const;
 private:
  std::map<int, std::vector<int>> adj_;
};
