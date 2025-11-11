#pragma once
#include <string>

class ExpressionParser {
public:
    double evaluate(const std::string& expression);
    
private:
    // Parsing methods
    double parseExpression(const std::string& expr, size_t& pos);
    double parseTerm(const std::string& expr, size_t& pos);
    double parseFactor(const std::string& expr, size_t& pos);
    double parseNumber(const std::string& expr, size_t& pos);
    double parseFunction(const std::string& expr, size_t& pos);
    
    // Utility methods
    void skipWhitespace(const std::string& expr, size_t& pos);
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    std::string extractFunctionName(const std::string& expr, size_t& pos);
};
