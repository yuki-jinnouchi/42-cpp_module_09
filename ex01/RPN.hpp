#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN {
 public:
  static double evaluate(const std::string& expression);

 private:
  // Orthodox canonical form
  RPN();
  ~RPN();
  RPN(const RPN& other);
  RPN& operator=(const RPN& other);

  // Utility functions
  static bool isOperator(const char& c);
  static bool isNumber(const char& c);
  static double performOperation(double a, double b, char c);
};

#endif // RPN_HPP
