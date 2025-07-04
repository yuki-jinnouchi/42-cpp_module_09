// main.cpp for PmergeMe - Main program for submission

#include <iostream>
#include <sstream>

#include "PmergeMe.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " [positive integers]" << std::endl;
    return 1;
  }

  PmergeMe sorter;
  for (int i = 1; i < argc; ++i) {
    std::istringstream iss(argv[i]);
    int value;
    if (!(iss >> value) || value < 0) {
      std::cerr << "Error: Invalid input '" << argv[i] << "'" << std::endl;
      return 1;
    }
    sorter.addData(value);
    sorter.addCountableData(value);
  }

  std::cout << "Before: " << std::endl;
  sorter.printData();

  sorter.sortData();

  std::cout << "\nAfter: " << std::endl;
  sorter.printData();

  sorter.sortCountableData();

  return 0;
}
