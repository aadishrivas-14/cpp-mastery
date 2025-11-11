# C++ Language Fundamentals

## Variables and Types
```cpp
// Fundamental types
int age = 25;
double price = 99.99;
char grade = 'A';
bool isActive = true;
auto value = 42;  // Type deduction

// Constants
const int MAX_SIZE = 100;
constexpr double PI = 3.14159;

// References and pointers
int x = 10;
int& ref = x;     // Reference
int* ptr = &x;    // Pointer
```

## Control Structures
```cpp
// Conditionals
if (condition) {
    // code
} else if (other) {
    // code
} else {
    // code
}

// Switch
switch (value) {
    case 1: break;
    case 2: break;
    default: break;
}

// Loops
for (int i = 0; i < 10; ++i) { }
while (condition) { }
do { } while (condition);

// Range-based for (C++11)
for (const auto& item : container) { }
```

## Functions
```cpp
// Basic function
int add(int a, int b) {
    return a + b;
}

// Function overloading
double add(double a, double b) {
    return a + b;
}

// Default parameters
void print(const std::string& msg, int count = 1);

// Lambda expressions (C++11)
auto lambda = [](int x) { return x * 2; };
auto capture = [&](int x) { return x + external_var; };
```

## Arrays and Containers
```cpp
// C-style arrays
int arr[10];
int init[] = {1, 2, 3, 4, 5};

// std::array (C++11)
std::array<int, 5> arr = {1, 2, 3, 4, 5};

// std::vector
std::vector<int> vec = {1, 2, 3, 4, 5};
vec.push_back(6);
vec.emplace_back(7);
```

## String Handling
```cpp
#include <string>

std::string str = "Hello";
str += " World";
str.append("!");

// String operations
size_t pos = str.find("World");
std::string sub = str.substr(0, 5);
str.replace(pos, 5, "C++");
```
