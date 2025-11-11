#include <gtest/gtest.h>
#include "unique_ptr.h"
#include "shared_ptr.h"
#include "weak_ptr.h"

// Test helper class
class TestObject {
public:
    TestObject(int val = 0) : value(val) { ++instance_count; }
    ~TestObject() { --instance_count; }
    int getValue() const { return value; }
    void setValue(int val) { value = val; }
    
    static int instance_count;
private:
    int value;
};

int TestObject::instance_count = 0;

class SmartPointersTest : public ::testing::Test {
protected:
    void SetUp() override {
        TestObject::instance_count = 0;
    }
    
    void TearDown() override {
        EXPECT_EQ(TestObject::instance_count, 0) << "Memory leak detected!";
    }
};

// unique_ptr tests
TEST_F(SmartPointersTest, UniquePtrBasicFunctionality) {
    {
        my::unique_ptr<TestObject> ptr(new TestObject(42));
        EXPECT_EQ(TestObject::instance_count, 1);
        EXPECT_EQ(ptr->getValue(), 42);
        EXPECT_EQ((*ptr).getValue(), 42);
    }
    EXPECT_EQ(TestObject::instance_count, 0);
}

TEST_F(SmartPointersTest, UniquePtrMoveSemantics) {
    my::unique_ptr<TestObject> ptr1(new TestObject(10));
    EXPECT_EQ(TestObject::instance_count, 1);
    
    my::unique_ptr<TestObject> ptr2 = std::move(ptr1);
    EXPECT_EQ(TestObject::instance_count, 1);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(ptr2->getValue(), 10);
}

TEST_F(SmartPointersTest, UniquePtrReset) {
    my::unique_ptr<TestObject> ptr(new TestObject(5));
    EXPECT_EQ(TestObject::instance_count, 1);
    
    ptr.reset(new TestObject(15));
    EXPECT_EQ(TestObject::instance_count, 1);
    EXPECT_EQ(ptr->getValue(), 15);
    
    ptr.reset();
    EXPECT_EQ(TestObject::instance_count, 0);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(SmartPointersTest, UniquePtrRelease) {
    my::unique_ptr<TestObject> ptr(new TestObject(20));
    TestObject* raw_ptr = ptr.release();
    
    EXPECT_EQ(TestObject::instance_count, 1);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_NE(raw_ptr, nullptr);
    EXPECT_EQ(raw_ptr->getValue(), 20);
    
    delete raw_ptr; // Manual cleanup after release
}

// shared_ptr tests
TEST_F(SmartPointersTest, SharedPtrBasicFunctionality) {
    {
        my::shared_ptr<TestObject> ptr(new TestObject(30));
        EXPECT_EQ(TestObject::instance_count, 1);
        EXPECT_EQ(ptr.use_count(), 1);
        EXPECT_EQ(ptr->getValue(), 30);
    }
    EXPECT_EQ(TestObject::instance_count, 0);
}

TEST_F(SmartPointersTest, SharedPtrReferenceCounting) {
    my::shared_ptr<TestObject> ptr1(new TestObject(40));
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(TestObject::instance_count, 1);
    
    {
        my::shared_ptr<TestObject> ptr2 = ptr1;
        EXPECT_EQ(ptr1.use_count(), 2);
        EXPECT_EQ(ptr2.use_count(), 2);
        EXPECT_EQ(TestObject::instance_count, 1);
        
        {
            my::shared_ptr<TestObject> ptr3 = ptr2;
            EXPECT_EQ(ptr1.use_count(), 3);
            EXPECT_EQ(ptr2.use_count(), 3);
            EXPECT_EQ(ptr3.use_count(), 3);
            EXPECT_EQ(TestObject::instance_count, 1);
        }
        
        EXPECT_EQ(ptr1.use_count(), 2);
        EXPECT_EQ(ptr2.use_count(), 2);
        EXPECT_EQ(TestObject::instance_count, 1);
    }
    
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(TestObject::instance_count, 1);
}

TEST_F(SmartPointersTest, SharedPtrReset) {
    my::shared_ptr<TestObject> ptr1(new TestObject(50));
    my::shared_ptr<TestObject> ptr2 = ptr1;
    
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(TestObject::instance_count, 1);
    
    ptr1.reset();
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(TestObject::instance_count, 1);
    
    ptr2.reset();
    EXPECT_EQ(TestObject::instance_count, 0);
}

// weak_ptr tests
TEST_F(SmartPointersTest, WeakPtrBasicFunctionality) {
    my::weak_ptr<TestObject> weak;
    EXPECT_TRUE(weak.expired());
    EXPECT_EQ(weak.use_count(), 0);
    
    {
        my::shared_ptr<TestObject> shared(new TestObject(60));
        weak = shared;
        
        EXPECT_FALSE(weak.expired());
        EXPECT_EQ(weak.use_count(), 1);
        EXPECT_EQ(TestObject::instance_count, 1);
        
        auto locked = weak.lock();
        EXPECT_NE(locked, nullptr);
        EXPECT_EQ(locked->getValue(), 60);
        EXPECT_EQ(weak.use_count(), 2);
    }
    
    EXPECT_TRUE(weak.expired());
    EXPECT_EQ(weak.use_count(), 0);
    EXPECT_EQ(TestObject::instance_count, 0);
}

TEST_F(SmartPointersTest, WeakPtrBreaksCycles) {
    struct Node {
        int value;
        my::shared_ptr<Node> next;
        my::weak_ptr<Node> parent;
        
        Node(int v) : value(v) {}
    };
    
    {
        auto node1 = my::shared_ptr<Node>(new Node(1));
        auto node2 = my::shared_ptr<Node>(new Node(2));
        
        node1->next = node2;
        node2->parent = node1; // weak_ptr breaks the cycle
        
        EXPECT_EQ(node1.use_count(), 1);
        EXPECT_EQ(node2.use_count(), 2); // shared by node1->next and node2
    }
    // No memory leak should occur
}

// Custom deleter tests
TEST_F(SmartPointersTest, UniquePtrWithCustomDeleter) {
    bool deleted = false;
    auto deleter = [&deleted](TestObject* ptr) {
        deleted = true;
        delete ptr;
    };
    
    {
        my::unique_ptr<TestObject, decltype(deleter)> ptr(new TestObject(70), deleter);
        EXPECT_EQ(TestObject::instance_count, 1);
        EXPECT_FALSE(deleted);
    }
    
    EXPECT_TRUE(deleted);
    EXPECT_EQ(TestObject::instance_count, 0);
}

// Array support tests
TEST_F(SmartPointersTest, UniquePtrArraySupport) {
    {
        my::unique_ptr<TestObject[]> ptr(new TestObject[3]{TestObject(1), TestObject(2), TestObject(3)});
        EXPECT_EQ(TestObject::instance_count, 3);
        EXPECT_EQ(ptr[0].getValue(), 1);
        EXPECT_EQ(ptr[1].getValue(), 2);
        EXPECT_EQ(ptr[2].getValue(), 3);
    }
    EXPECT_EQ(TestObject::instance_count, 0);
}

// make_unique and make_shared tests
TEST_F(SmartPointersTest, MakeUnique) {
    {
        auto ptr = my::make_unique<TestObject>(80);
        EXPECT_EQ(TestObject::instance_count, 1);
        EXPECT_EQ(ptr->getValue(), 80);
    }
    EXPECT_EQ(TestObject::instance_count, 0);
}

TEST_F(SmartPointersTest, MakeShared) {
    {
        auto ptr = my::make_shared<TestObject>(90);
        EXPECT_EQ(TestObject::instance_count, 1);
        EXPECT_EQ(ptr->getValue(), 90);
        EXPECT_EQ(ptr.use_count(), 1);
    }
    EXPECT_EQ(TestObject::instance_count, 0);
}
