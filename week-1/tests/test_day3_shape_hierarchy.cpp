// Week 1, Day 3: OOP Basics + Shape Hierarchy
// Project Status: Shape Hierarchy with Polymorphism

#include "shape.h"
#include <gtest/gtest.h>

TEST(Day3ShapeHierarchyTest, CircleArea) {
  Circle c(5.0);
  EXPECT_NEAR(c.area(), 78.54, 0.01);
}

TEST(Day3ShapeHierarchyTest, RectangleArea) {
  Rectangle r(4.0, 5.0);
  EXPECT_DOUBLE_EQ(r.area(), 20.0);
}

TEST(Day3ShapeHierarchyTest, Polymorphism) {
  Shape* shape = new Circle(5.0);
  EXPECT_NEAR(shape->area(), 78.54, 0.01);
  delete shape;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
