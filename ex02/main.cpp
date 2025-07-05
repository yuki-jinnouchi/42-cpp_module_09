#include <time.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "PmergeMe.hpp"

double time_diff_us(struct timespec start, struct timespec end) {
  // // Check resolution
  // struct timespec res;
  // clock_getres(CLOCK_MONOTONIC, &res);
  // std::cout << "Resolution: " << res.tv_nsec << " ns" << std::endl;

  double start_us =
      start.tv_sec * 1e6 + static_cast<double>(start.tv_nsec) / 1e3;
  double end_us = end.tv_sec * 1e6 + static_cast<double>(end.tv_nsec) / 1e3;
  return end_us - start_us;
}

void basic_main(PmergeMe &sorter, int input_size) {
  // Before output
  std::cout << "Before:  ";
  sorter.printData();

  // Sort and measure time
  struct timespec startVector, endVector;
  struct timespec startDeque, endDeque;

  clock_gettime(CLOCK_MONOTONIC, &startVector);
  sorter.sortVector();
  clock_gettime(CLOCK_MONOTONIC, &endVector);
  double time_vector = time_diff_us(startVector, endVector);

  clock_gettime(CLOCK_MONOTONIC, &startDeque);
  sorter.sortDeque();
  clock_gettime(CLOCK_MONOTONIC, &endDeque);
  double time_deque = time_diff_us(startDeque, endDeque);

  // After output
  std::cout << "After:   ";
  sorter.printData();

  std::cout << std::fixed << std::setprecision(5);
  std::cout << "Time to process a range of " << input_size
            << " elements with std::vector : " << time_vector << " us"
            << std::endl;
  std::cout << "Time to process a range of " << input_size
            << " elements with std::deque  : " << time_deque << " us"
            << std::endl;
}

void test_main(PmergeMe &sorter) {
  std::cout << "\n=== CountableInt Sort ===" << std::endl;

  // printCountableData();

  CountableInt::resetCount();
  std::cout << "Init ";
  sorter.printComparisonCounts();

  sorter.sortCountableVector();
  int vector_comparisons = CountableInt::getComparisonCount();

  std::cout << "count std::vector : " << vector_comparisons << std::endl;

  // CountableInt::resetCount();
  // std::cout << "Init ";
  // sorter.printComparisonCounts();

  // sorter.sortCountableDeque();
  // int deque_comparisons = CountableInt::getComparisonCount();

  // std::cout << "count std::deque  : " << deque_comparisons << std::endl;

  std::cout << "Is sorted data: " << (sorter.isSortedData() ? "Yes" : "No")
            << std::endl;

  // printCountableData();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " [positive integers]" << std::endl;
    return 1;
  }

  PmergeMe sorter;
  // int input_size = argc - 1;

  // Parse arguments and add data
  for (int i = 1; i < argc; ++i) {
    std::istringstream iss(argv[i]);
    int value;
    if (!(iss >> value) || value < 0) {
      std::cerr << "Error" << std::endl;
      return 1;
    }
    sorter.addData(value);
    sorter.addCountableData(value);
  }

  // basic_main(sorter, input_size);
  test_main(sorter);

  return 0;
}
