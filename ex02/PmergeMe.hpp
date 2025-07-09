#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <iostream>
#include <string>
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

  // Merge Insertion Sort for vector
  template <typename iterator>
  void mergeInsertionSortVec(iterator first, iterator last);

  template <typename T>
  std::pair<std::vector<T>, std::vector<T> > extract(typename std::vector<T>::iterator first,
                                        typename std::vector<T>::iterator last);
  template <typename T>
  void popIndexes(std::vector<T> &vec);
  template <typename T>
  std::vector<T> mergeVectors(std::vector<T> &winners, std::vector<T> &losers);
  template <typename T>
  void printVector(std::vector<T> &vec, std::string explain) const;

  // Merge Insertion Sort for deque
  template <typename iterator>
  void mergeInsertionSortDeque(iterator first, iterator last);

  template <typename T>
  std::pair<std::deque<T>, std::deque<T> > extract(typename std::deque<T>::iterator first,
                                        typename std::deque<T>::iterator last);
  template <typename T>
  void popIndexes(std::deque<T> &vec);
  template <typename T>
  std::deque<T> mergeVectors(std::deque<T> &winners, std::deque<T> &losers);
  template <typename T>
  void printVector(std::deque<T> &vec, std::string explain) const;

};

#endif  // PMERGEME_HPP
