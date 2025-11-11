#include "hash_table.h"
#include "graph.h"
#include <gtest/gtest.h>
#include <string>

TEST(Day6HashTableTest, InsertAndFind) {
  HashTable<std::string, int> ht;
  ht.insert("one", 1);
  int val;
  EXPECT_TRUE(ht.find("one", val));
  EXPECT_EQ(val, 1);
}

TEST(Day6GraphTest, AddEdge) {
  Graph g;
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  auto neighbors = g.getNeighbors(1);
  EXPECT_EQ(neighbors.size(), 2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
