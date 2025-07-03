#include <iostream>
#include <string>
#include "RPN.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <RPN expression>" << std::endl;
      return 1;
    }
    double result = RPN::evaluate(argv[1]);
    std::cout << result << std::endl;
  } catch (const std::runtime_error& e) {
    std::cerr << "Error";
    // std::cerr << ": " << e.what();
    std::cerr << std::endl;
    return 1;
  }
  return 0;
}
