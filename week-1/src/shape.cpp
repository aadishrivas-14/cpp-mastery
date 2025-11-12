#include "shape.h"

#include <cmath>

// ## In One Sentence
//
// Create a family of shapes where each shape knows how to calculate its own measurements, and you
// can treat all shapes the same way even though they calculate differently.
// ## Key OOP Concepts

// ### 1. Inheritance
// Circle inherits from Shape
// = Circle IS A Shape
// = Circle gets all Shape's features

// ### 2. Virtual Functions
// Shape says: "area() is virtual"
// = Each child can implement it differently
// = Circle calculates area one way
// = Rectangle calculates area another way

// ### 3. Polymorphism
// Shape* s = new Circle(5);
// s->area();  // Calls Circle's area(), not Shape's!

// Magic: Even though we say "it's a Shape", the computer knows it's really a Circle and uses
// Circle's calculation.

// TODO: Implement Circle class

Circle::Circle(double radius) : radius_(radius) {}


// Alternative (also valid):
// cpp
// Circle::Circle(double radius) {
//   radius_ = radius;
// }


double Circle::area() const { return M_PI * radius_ * radius_; }

double Circle::perimeter() const { return 2 * M_PI * radius_; }

// TODO: Implement Rectangle class

Rectangle::Rectangle(double width, double height) : width_(width), height_(height) {}

double Rectangle::area() const { return width_ * height_; }

double Rectangle::perimeter() const { return 2 * (width_ + height_); }
