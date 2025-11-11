#include <gtest/gtest.h>
#include "vector.h"
#include "list.h"
#include "map.h"

// Vector tests
class VectorTest : public ::testing::Test {
protected:
    my::vector<int> vec;
};

TEST_F(VectorTest, DefaultConstruction) {
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
    EXPECT_GE(vec.capacity(), 0);
}

TEST_F(VectorTest, PushBackIncreasesSize) {
    vec.push_back(42);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_FALSE(vec.empty());
    EXPECT_EQ(vec[0], 42);
}

TEST_F(VectorTest, ResizesWhenCapacityExceeded) {
    size_t initial_capacity = vec.capacity();
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }
    EXPECT_GT(vec.capacity(), initial_capacity);
    EXPECT_EQ(vec.size(), 100);
}

TEST_F(VectorTest, IteratorSupport) {
    for (int i = 0; i < 5; ++i) {
        vec.push_back(i);
    }
    
    int expected = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        EXPECT_EQ(*it, expected++);
    }
    
    // Range-based for loop
    expected = 0;
    for (const auto& value : vec) {
        EXPECT_EQ(value, expected++);
    }
}

TEST_F(VectorTest, EmplaceBack) {
    struct Point { int x, y; Point(int x, int y) : x(x), y(y) {} };
    my::vector<Point> points;
    
    points.emplace_back(1, 2);
    EXPECT_EQ(points.size(), 1);
    EXPECT_EQ(points[0].x, 1);
    EXPECT_EQ(points[0].y, 2);
}

TEST_F(VectorTest, InsertAndErase) {
    vec = {1, 2, 4, 5};
    
    auto it = vec.insert(vec.begin() + 2, 3);
    EXPECT_EQ(*it, 3);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[2], 3);
    
    vec.erase(vec.begin() + 1);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[1], 3);
}

// List tests
class ListTest : public ::testing::Test {
protected:
    my::list<int> lst;
};

TEST_F(ListTest, PushFrontAndBack) {
    lst.push_back(2);
    lst.push_front(1);
    lst.push_back(3);
    
    EXPECT_EQ(lst.size(), 3);
    EXPECT_EQ(lst.front(), 1);
    EXPECT_EQ(lst.back(), 3);
}

TEST_F(ListTest, BidirectionalIterator) {
    lst = {1, 2, 3, 4, 5};
    
    auto it = lst.end();
    --it;
    EXPECT_EQ(*it, 5);
    --it;
    EXPECT_EQ(*it, 4);
}

TEST_F(ListTest, InsertAndErase) {
    lst = {1, 3, 5};
    
    auto it = lst.begin();
    ++it;
    lst.insert(it, 2);
    
    EXPECT_EQ(lst.size(), 4);
    it = lst.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 5);
}

TEST_F(ListTest, Splice) {
    my::list<int> other = {10, 20, 30};
    lst = {1, 2, 3};
    
    lst.splice(lst.begin() + 1, other);
    EXPECT_EQ(lst.size(), 6);
    EXPECT_TRUE(other.empty());
}

// Map tests
class MapTest : public ::testing::Test {
protected:
    my::map<int, std::string> mp;
};

TEST_F(MapTest, InsertAndFind) {
    mp.insert({1, "one"});
    mp.insert({2, "two"});
    
    auto it = mp.find(1);
    EXPECT_NE(it, mp.end());
    EXPECT_EQ(it->second, "one");
    
    it = mp.find(3);
    EXPECT_EQ(it, mp.end());
}

TEST_F(MapTest, SubscriptOperator) {
    mp[1] = "one";
    mp[2] = "two";
    
    EXPECT_EQ(mp[1], "one");
    EXPECT_EQ(mp[2], "two");
    EXPECT_EQ(mp.size(), 2);
}

TEST_F(MapTest, OrderedIteration) {
    mp[3] = "three";
    mp[1] = "one";
    mp[2] = "two";
    
    std::vector<int> keys;
    for (const auto& pair : mp) {
        keys.push_back(pair.first);
    }
    
    EXPECT_EQ(keys, std::vector<int>({1, 2, 3}));
}

TEST_F(MapTest, EraseByKey) {
    mp[1] = "one";
    mp[2] = "two";
    mp[3] = "three";
    
    EXPECT_EQ(mp.erase(2), 1);
    EXPECT_EQ(mp.size(), 2);
    EXPECT_EQ(mp.find(2), mp.end());
}

// Custom allocator tests
TEST(CustomAllocatorTest, WorksWithVector) {
    my::vector<int, my::pool_allocator<int>> vec;
    
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

// Exception safety tests
TEST(ExceptionSafetyTest, VectorStrongGuarantee) {
    struct ThrowingType {
        static int copy_count;
        int value;
        
        ThrowingType(int v) : value(v) {}
        ThrowingType(const ThrowingType& other) : value(other.value) {
            if (++copy_count > 3) throw std::runtime_error("Copy failed");
        }
    };
    
    ThrowingType::copy_count = 0;
    my::vector<ThrowingType> vec;
    
    vec.emplace_back(1);
    vec.emplace_back(2);
    
    EXPECT_THROW(vec.push_back(ThrowingType(3)), std::runtime_error);
    EXPECT_EQ(vec.size(), 2); // Strong guarantee
}
