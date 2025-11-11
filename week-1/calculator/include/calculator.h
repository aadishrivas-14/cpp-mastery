#pragma once

class Calculator {
public:
    // Basic arithmetic operations
    double add(double a, double b) const;
    double subtract(double a, double b) const;
    double multiply(double a, double b) const;
    double divide(double a, double b) const;
    
    // Advanced operations
    double power(double base, double exponent) const;
    double sqrt(double value) const;
    long long factorial(int n) const;
    
    // Memory functions
    void memoryStore(double value);
    double memoryRecall() const;
    void memoryAdd(double value);
    void memoryClear();
    
private:
    double memory_ = 0.0;
};
