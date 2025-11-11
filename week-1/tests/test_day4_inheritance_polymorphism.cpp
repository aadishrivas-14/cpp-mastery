// Week 1, Day 4: Inheritance + Polymorphism
// Project Status: Advanced OOP concepts

#include "animal.h"
#include <gtest/gtest.h>

TEST(Day4InheritanceTest, DogSpeak) {
  Dog dog;
  EXPECT_EQ(dog.speak(), "Woof");
}

TEST(Day4InheritanceTest, CatSpeak) {
  Cat cat;
  EXPECT_EQ(cat.speak(), "Meow");
}

TEST(Day4PolymorphismTest, VirtualFunction) {
  Animal* animal = new Dog();
  EXPECT_EQ(animal->speak(), "Woof");
  delete animal;
  
  animal = new Cat();
  EXPECT_EQ(animal->speak(), "Meow");
  delete animal;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
