#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>

// Orthodox Canonical Form
PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : vector_data(other.vector_data),
      deque_data(other.deque_data),
      countable_vector_data(other.countable_vector_data),
      countable_deque_data(other.countable_deque_data) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
    vector_data = other.vector_data;
    deque_data = other.deque_data;
    countable_vector_data = other.countable_vector_data;
    countable_deque_data = other.countable_deque_data;
  }
  return *this;
}

// Required methods for int type
void PmergeMe::addData(int value) {
  vector_data.push_back(value);
  deque_data.push_back(value);
}

void PmergeMe::sortData() {
  sortVector();
  sortDeque();
}

void PmergeMe::sortVector() {
  std::sort(vector_data.begin(), vector_data.end());
}

void PmergeMe::sortDeque() {
  std::sort(deque_data.begin(), deque_data.end());
}

void PmergeMe::printData() const {
  std::cout << "Vector data: ";
  for (std::vector<int>::const_iterator it = vector_data.begin();
       it != vector_data.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "Deque data: ";
  for (std::deque<int>::const_iterator it = deque_data.begin();
       it != deque_data.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

// Countable Int methods
void PmergeMe::addCountableData(int value) {
  countable_vector_data.push_back(CountableInt(value));
  countable_deque_data.push_back(CountableInt(value));
}

void PmergeMe::sortCountableData() {
  std::cout << "\n=== CountableInt Sort ===" << std::endl;
  printCountableData();

  CountableInt::resetCount();
  std::cout << "Init ";
  printComparisonCounts();

  sortCountableVector();
  int vector_comparisons = CountableInt::getComparisonCount();

  CountableInt::resetCount();
  std::cout << "Init ";
  printComparisonCounts();

  sortCountableDeque();
  int deque_comparisons = CountableInt::getComparisonCount();

  std::cout << "count std::vector : " << vector_comparisons << std::endl;
  std::cout << "count std::deque  : " << deque_comparisons << std::endl;

  printCountableData();
}

void PmergeMe::sortCountableVector() {
  
}

void PmergeMe::sortCountableDeque() {
  // マージインサーションソートの実装
  std::sort(countable_deque_data.begin(), countable_deque_data.end());
}

void PmergeMe::printComparisonCounts() const {
  std::cout << "Count : " << CountableInt::getComparisonCount() << std::endl;
}

void PmergeMe::printCountableData() const {
  std::cout << "Countable Vector data: ";
  for (std::vector<CountableInt>::const_iterator it =
           countable_vector_data.begin();
       it != countable_vector_data.end(); ++it) {
    CountableInt item = *it;
    std::cout << item.getValue() << " ";
  }
  std::cout << std::endl;

  std::cout << "Countable Deque data: ";
  for (std::deque<CountableInt>::const_iterator it =
           countable_deque_data.begin();
       it != countable_deque_data.end(); ++it) {
    CountableInt item = *it;
    std::cout << item.getValue() << " ";
  }
  std::cout << std::endl;
}
