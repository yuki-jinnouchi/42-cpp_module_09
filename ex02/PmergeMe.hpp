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
  void sortVector();
  void sortDeque();
  void printData() const;

  // CountableInt specific methods
  void addCountableData(int value);
  void sortCountableVector();
  void sortCountableDeque();
  void printCountableData() const;
  void printComparisonCounts() const;
  bool isSortedData() const;

  private:
  // Member variables
  std::vector<int> _vectorData;
  std::deque<int> _dequeData;

  // CountableInt for testing
  std::vector<CountableInt> _countableVectorData;
  std::deque<CountableInt> _countableDequeData;

  // Calculate insertion order using Jacobsthal sequence
  std::vector<size_t> get_jacobsthal_insertion_order(size_t n);

  // Merge Insertion Sort template
  template <typename Container>
  Container mergeInsertionSort(const Container &container);
};

#endif  // PMERGEME_HPP
