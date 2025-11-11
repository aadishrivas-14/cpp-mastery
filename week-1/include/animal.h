#pragma once
#include <string>

/**
 * TODO: Implement Animal Hierarchy (Inheritance & Polymorphism)
 * 
 * Requirements:
 * - Abstract base class Animal with pure virtual speak()
 * - Dog class: speak() returns "Woof"
 * - Cat class: speak() returns "Meow"
 * 
 * Demonstrates:
 * - Virtual functions
 * - Polymorphism
 * - Runtime dispatch
 */

class Animal {
 public:
  virtual ~Animal() = default;
  virtual std::string speak() const = 0;
};

class Dog : public Animal {
 public:
  std::string speak() const override;
};

class Cat : public Animal {
 public:
  std::string speak() const override;
};
