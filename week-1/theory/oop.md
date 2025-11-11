# Object-Oriented Programming

## Classes and Objects
```cpp
class BankAccount {
private:
    std::string owner;
    double balance;
    
public:
    BankAccount(const std::string& name, double initial = 0.0)
        : owner(name), balance(initial) {}
    
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double getBalance() const { return balance; }
    const std::string& getOwner() const { return owner; }
};
```

## Inheritance
```cpp
class SavingsAccount : public BankAccount {
private:
    double interestRate;
    
public:
    SavingsAccount(const std::string& name, double rate, double initial = 0.0)
        : BankAccount(name, initial), interestRate(rate) {}
    
    void applyInterest() {
        double interest = getBalance() * interestRate / 100;
        deposit(interest);
    }
};
```

## Polymorphism
```cpp
class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};

// Usage
std::unique_ptr<Shape> shape = std::make_unique<Circle>(5.0);
double area = shape->area();  // Virtual function call
```

## Operator Overloading
```cpp
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        return os << c.real << " + " << c.imag << "i";
    }
};
```
