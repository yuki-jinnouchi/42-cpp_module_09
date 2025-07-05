#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>
#include <utility>  // std::pair
#include <vector>

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
  // マージインサーションソートの実装
  std::sort(vector_data.begin(), vector_data.end());
}

void PmergeMe::sortDeque() {
  // マージインサーションソートの実装
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
  // マージインサーションソートの実装
  countable_vector_data =
      merge_insertion_sort(countable_vector_data);
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

// 前方宣言
std::vector<int> merge_insertion_sort(const std::vector<int> &vec);

std::vector<int> merge_insertion_sort(const std::vector<int> &vec) {
  if (vec.size() <= 1) return vec;

  // make pairs
  std::vector<std::pair<int, int>> pairs;
  size_t i = 0;
  while (i + 1 < vec.size()) {
    int a = vec[i];
    int b = vec[i + 1];
    if (a < b)
      pairs.push_back(std::make_pair(b, a));
    else
      pairs.push_back(std::make_pair(a, b));
    i += 2;
  }

  // treat orphan if exists
  bool has_orphan = (vec.size() % 2 == 1);
  int orphan = vec[vec.size() - 1];
  if (has_orphan) pairs.push_back(std::make_pair(orphan, -1));

  // Sort larger values
  std::vector<int> larger_values;
  for (size_t j = 0; j < pairs.size(); ++j) {
    larger_values.push_back(pairs[j].first);
  }

  std::vector<int> sorted = merge_insertion_sort(larger_values);

  std::vector<size_t> insert_order =
      get_jacobsthal_insertion_order(pairs.size());

  for (size_t j = 0; j < insert_order.size(); ++j) {
    size_t idx = insert_order[j];
    int small = pairs[idx].second;
    if (small == -1) continue;
    std::vector<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), small);
    sorted.insert(pos, small);
  }

  return sorted;
}

std::vector<size_t> get_jacobsthal_insertion_order(size_t n) {
  std::vector<size_t> result;
  result.push_back(0);
  size_t j1 = 1;
  size_t j2 = 0;
  while (true) {
    size_t j = j1 + 2 * j2;
    if (j >= n) break;
    result.push_back(j);
    j2 = j1;
    j1 = j;
  }
  // 残りのインデックスを補完
  for (size_t i = 0; i < n; ++i) {
    if (std::find(result.begin(), result.end(), i) == result.end())
      result.push_back(i);
  }
  return result;
}
