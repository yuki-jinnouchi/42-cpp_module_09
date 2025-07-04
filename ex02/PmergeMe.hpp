#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

#include "CountableInt.hpp"

class PmergeMe {
 public:
  // Orthodox Canonical Form
  PmergeMe();
  ~PmergeMe();
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);

  // Function to process the input data
  void addData(int value);
  void sortData();
  void printData() const;

  // CountableInt版のメソッド
  void addCountableData(int value);
  void sortCountableData();
  void printComparisonCounts() const;
  void printCountableData() const;

 private:
  // Member variables
  std::vector<int> vector_data;
  std::deque<int> deque_data;

  // Function
  void sortVector();
  void sortDeque();

  // CountableInt
  std::vector<CountableInt> countable_vector_data;
  std::deque<CountableInt> countable_deque_data;

  // CountableInt
  void sortCountableVector();
  void sortCountableDeque();
};

#endif  // PMERGEME_HPP
