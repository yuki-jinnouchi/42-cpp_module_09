#include "RPN.hpp"

#include <sstream>
#include <stack>
#include <list>
#include <stdexcept>
// #include <iostream>

// Orthodox canonical form
RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) {
  (void)other;
}

RPN& RPN::operator=(const RPN& other) {
  if (this != &other) {
    // No data members to copy
  }
  return *this;
}

// Member functions
double RPN::evaluate(const std::string& expression) {
  std::stack<double, std::list<double> > stack;
  for (size_t i = 0; i < expression.length(); i++) {
    char c = expression[i];
    if (c == ' ') continue;
    if (isNumber(c)) {
      double num = expression[i] - '0';
      stack.push(num);
      // std::cout << "Pushing number: " << num << std::endl;
      continue;
    }
    if (isOperator(c)) {
      if (stack.size() < 2) throw std::runtime_error("Stack underflow");
      double b = stack.top();
      stack.pop();
      double a = stack.top();
      stack.pop();
      double tmp = performOperation(a, b, c);
      stack.push(tmp);
      // std::cout << "Performing operation: " << a << " " << c << " " << b << "
      // = " << tmp << std::endl;
      continue;
    }
  }
  if (stack.size() != 1) throw std::runtime_error("Final Stack size is not 1");
  return stack.top();
}

bool RPN::isOperator(const char& c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isNumber(const char& c) {
  if (!std::isdigit(c)) return false;
  return true;
}

double RPN::performOperation(double a, double b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      if (b == 0) throw std::runtime_error("Division by zero");
      return a / b;
    default:
      throw std::runtime_error("Invalid operator");
  }
}
