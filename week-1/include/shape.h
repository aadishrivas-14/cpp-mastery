#pragma once

/**
 * TODO: Implement Shape Hierarchy (OOP Basics)
 * 
 * Requirements:
 * - Abstract base class Shape with pure virtual methods
 * - Circle class: area() and perimeter() using radius
 * - Rectangle class: area() and perimeter() using width and height
 * 
 * Formulas:
 * - Circle area: π * r²
 * - Circle perimeter: 2 * π * r
 * - Rectangle area: width * height
 * - Rectangle perimeter: 2 * (width + height)
 * 
 * Use M_PI from <cmath> for π
 */

class Shape {
 public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
};

class Circle : public Shape {
 public:
  explicit Circle(double radius);
  double area() const override;
  double perimeter() const override;
 private:
  double radius_;
};

class Rectangle : public Shape {
 public:
  Rectangle(double width, double height);
  double area() const override;
  double perimeter() const override;
 private:
  double width_;
  double height_;
};
