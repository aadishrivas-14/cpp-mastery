# Week 1 Interview Questions

## Day 1: Calculator (Basic C++)

### Beginner Level

1. What is a class in C++?

2. What does `const` mean after a method declaration?
   ```cpp
   double add(double a, double b) const;
   ```

3. What's the difference between `int` and `double`?

4. What does `return` do?

5. What is a parameter vs an argument?
   ```cpp
   double add(double a, double b);  // a, b are ?
   calc.add(2, 3);                  // 2, 3 are ?
   ```

### Intermediate Level

6. Why use `const` methods?

7. What's the difference between declaration and definition?
   ```cpp
   // Declaration (in .h)
   double add(double a, double b) const;
   
   // Definition (in .cpp)
   double Calculator::add(double a, double b) const {
     return a + b;
   }
   ```

8. What does `::` (scope resolution operator) mean?

9. Can you modify a `const` parameter?
   ```cpp
   void func(const int x) {
     x = 5;  // Is this allowed?
   }
   ```

10. What's the purpose of header guards or `#pragma once`?

---

## Day 2: Expression Parser (Strings, Vectors, Algorithms)

### Beginner Level

11. What is `std::string`?

12. What is `std::vector`?

13. How do you access a character in a string?
    ```cpp
    std::string s = "hello";
    char c = s[0];  // What is c?
    ```

14. What does `.push_back()` do?

15. What does `.size()` return?

### Intermediate Level

16. What is operator precedence? Give examples.

17. What's the difference between `size_t` and `int`?

18. How do you convert string to number?
    ```cpp
    std::string s = "123";
    // Convert to double?
    ```

19. What does `.erase()` do on a vector?

20. Explain this loop:
    ```cpp
    for (size_t i = 0; i < vec.size(); i++) { }
    ```

### Advanced Level

21. Why use two-pass algorithm for expression parsing?

22. What's the time complexity of vector.erase()?

23. How would you handle parentheses in expression parser?

24. What's the difference between `++i` and `i++`?

25. Why use iterators instead of indices?
    ```cpp
    vec.erase(vec.begin() + i);
    ```

---

## Day 3: Shape Hierarchy (OOP, Inheritance, Polymorphism)

### Beginner Level

26. What is inheritance?

27. What does `public` inheritance mean?
    ```cpp
    class Circle : public Shape { };
    ```

28. What is a base class vs derived class?

29. What does `override` keyword do?

30. What is a constructor?

### Intermediate Level

31. What is polymorphism?

32. What does `virtual` keyword do?

33. What is a pure virtual function?
    ```cpp
    virtual double area() const = 0;
    ```

34. What is an abstract class?

35. Why use member initializer list?
    ```cpp
    Circle(double r) : radius_(r) { }
    ```

36. What's the difference between these?
    ```cpp
    Circle c(5);      // vs
    Circle* c = new Circle(5);
    ```

37. Why trailing underscore for member variables?
    ```cpp
    double radius_;
    ```

38. What happens if you don't make destructor virtual?
    ```cpp
    Shape* s = new Circle(5);
    delete s;  // Problem?
    ```

39. Explain this:
    ```cpp
    Shape* shape = new Circle(5);
    shape->area();
    ```

40. What is `M_PI`?

### Advanced Level

41. What is a vtable (virtual table)?

42. What's the cost of virtual functions?

43. Can constructors be virtual?

44. Why must destructors be virtual in base classes?

45. What is the diamond problem in inheritance?

46. Explain early binding vs late binding.

47. Can you override a non-virtual function?

48. What is RAII?

49. How would you implement a Shape factory?

50. What's the difference between `override` and `final`?

---

## Coding Challenges

### Challenge 1: Calculator Extension
```cpp
// Add these methods to Calculator:
double power(double base, double exp);
double sqrt(double value);
long long factorial(int n);
```

### Challenge 2: Expression Parser Extension
```cpp
// Extend parser to handle:
"2+3*4-5"     // Multiple operations
"10/2/5"      // Chained division
"2.5+3.7"     // Decimal numbers
```

### Challenge 3: Shape Hierarchy Extension
```cpp
// Add new shapes:
class Triangle : public Shape {
  // Implement with 3 sides
};

class Square : public Rectangle {
  // Special case of rectangle
};
```

### Challenge 4: Polymorphism Practice
```cpp
// Write a function that:
void printShapeInfo(Shape* shape) {
  // Print area and perimeter of any shape
}
```

### Challenge 5: Memory Management
```cpp
// What's wrong with this code?
Shape* shape = new Circle(5);
shape->area();
// Missing something?
```

---

## Conceptual Questions

51. Why separate .h and .cpp files?

52. What is the compilation process?

53. What's the difference between `#include "file.h"` and `#include <file.h>`?

54. What is a namespace? Why `std::`?

55. What's the difference between struct and class?

56. What is encapsulation?

57. What are access specifiers?

58. What is method overloading?
    ```cpp
    double add(double a, double b);
    int add(int a, int b);
    ```

59. What is the `this` pointer?

60. What's the difference between pass-by-value and pass-by-reference?
    ```cpp
    void func1(int x);        // by value
    void func2(int& x);       // by reference
    void func3(const int& x); // const reference
    ```

---

## Debugging Questions

61. What's wrong here?
    ```cpp
    double Calculator::add(double a, double b) {
      return a + b
    }
    ```

62. What's the error?
    ```cpp
    Circle c;
    c.area();
    ```

63. Why doesn't this compile?
    ```cpp
    Shape s;
    ```

64. What's wrong?
    ```cpp
    std::vector<int> vec;
    vec[0] = 5;
    ```

65. Find the bug:
    ```cpp
    Circle::Circle(double radius) {
      radius = radius;
    }
    ```

---

## Best Practices Questions

66. Why use `const` correctness?

67. When should you use `explicit` keyword?
    ```cpp
    explicit Circle(double radius);
    ```

68. Why initialize members in initializer list?

69. What's the rule of three/five?

70. Why use smart pointers instead of raw pointers?

---

## Topics Covered

**Day 1:** Basic syntax, const correctness, class structure  
**Day 2:** STL containers, algorithms, string manipulation  
**Day 3:** OOP principles, inheritance, polymorphism, virtual functions

**Practice these concepts to master Week 1!**
