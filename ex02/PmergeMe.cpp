#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

// Orthodox Canonical Form
PmergeMe::PmergeMe() {
  _vectorData = std::vector<int>();
  _dequeData = std::deque<int>();
  _countableVectorData = std::vector<CountableInt>();
  _countableDequeData = std::deque<CountableInt>();
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _vectorData(other._vectorData),
      _dequeData(other._dequeData),
      _countableVectorData(other._countableVectorData),
      _countableDequeData(other._countableDequeData) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
    _vectorData = other._vectorData;
    _dequeData = other._dequeData;
    _countableVectorData = other._countableVectorData;
    _countableDequeData = other._countableDequeData;
  }
  return *this;
}

// Required methods for type int
void PmergeMe::addData(int value) {
  _vectorData.push_back(value);
  _dequeData.push_back(value);
}

void PmergeMe::sortVector() {
  _vectorData = mergeInsertionSort(_vectorData);
}

void PmergeMe::sortDeque() {
  _dequeData = mergeInsertionSort(_dequeData);
}

void PmergeMe::printData() const {
  for (std::vector<int>::const_iterator it = _vectorData.begin();
       it != _vectorData.end(); ++it) {
    std::cout << *it;
    if (it + 1 != _vectorData.end()) std::cout << " ";
  }
  std::cout << std::endl;
}

// CountableInt methods
void PmergeMe::addCountableData(int value) {
  _countableVectorData.push_back(CountableInt(value));
  _countableDequeData.push_back(CountableInt(value));
}

void PmergeMe::sortCountableVector() {
  _countableVectorData = mergeInsertionSort(_countableVectorData);
}

void PmergeMe::sortCountableDeque() {
  _countableDequeData = mergeInsertionSort(_countableDequeData);
}

void PmergeMe::printComparisonCounts() const {
  std::cout << "count        : " << CountableInt::getComparisonCount()
            << std::endl;
}

void PmergeMe::printCountableData() const {
  std::cout << "Countable Vector data: ";
  for (std::vector<CountableInt>::const_iterator it =
           _countableVectorData.begin();
       it != _countableVectorData.end(); ++it) {
    CountableInt item = *it;
    std::cout << item.getValue() << " ";
  }
  std::cout << std::endl;

  // std::cout << "Countable Deque data: ";
  // for (std::deque<CountableInt>::const_iterator it =
  //          _countableDequeData.begin();
  //      it != _countableDequeData.end(); ++it) {
  //   CountableInt item = *it;
  //   std::cout << item.getValue() << " ";
  // }
  // std::cout << std::endl;
}

bool PmergeMe::isSortedData() const {
  // Check if vector is sorted
  int temp = 0;
  for (std::vector<CountableInt>::const_iterator it =
           _countableVectorData.begin();
       it != _countableVectorData.end(); it++) {
    CountableInt item = *it;
    if (temp > item.getValue()) return false;
    temp = item.getValue();
  }

  // // Check if deque is sorted
  // for (size_t i = 1; i < _dequeData.size(); ++i) {
  //   if (_dequeData[i] < _dequeData[i - 1]) return false;
  // }

  return true;
}

std::vector<size_t> PmergeMe::getJInsertionOrder(size_t n) {
  std::vector<size_t> result = std::vector<size_t>();
  if (n == 0) return result;

  result.push_back(0);
  size_t j0 = 1;
  size_t j1 = 0;
  while (true) {
    size_t j = j0 + 2 * j1;
    if (j >= n) break;
    result.push_back(j);
    j1 = j0;
    j0 = j;
  }
  // 残りのインデックスを補完
  for (size_t i = 0; i < n; ++i) {
    if (std::find(result.begin(), result.end(), i) == result.end())
      result.push_back(i);
  }
  return result;
}

template <typename Container>
Container PmergeMe::mergeInsertionSort(const Container &container) {
  typedef typename Container::value_type T;

  if (container.size() <= 1) return container;

  // make pairs
  std::vector<std::pair<T, T> > pairs;
  typename Container::const_iterator it = container.begin();
  bool has_orphan = false;
  T orphan;

  while (it != container.end()) {
    T a = *it;
    ++it;
    if (it == container.end()) {
      // 奇数個の場合、最後の要素をorphanとして保存
      has_orphan = true;
      orphan = a;
      break;
    }
    T b = *it;
    ++it;

    if (a < b)
      pairs.push_back(std::make_pair(b, a));
    else
      pairs.push_back(std::make_pair(a, b));
  }

  // 大きい値でソート
  Container larger_values;
  for (size_t j = 0; j < pairs.size(); ++j) {
    larger_values.push_back(pairs[j].first);
  }

  Container sorted = mergeInsertionSort(larger_values);

  std::vector<size_t> insert_order = getJInsertionOrder(pairs.size());

  for (size_t j = 0; j < insert_order.size(); ++j) {
    size_t idx = insert_order[j];
    if (idx < pairs.size()) {
      T small = pairs[idx].second;
      typename Container::iterator pos =
          std::lower_bound(sorted.begin(), sorted.end(), small);
      sorted.insert(pos, small);
    }
  }

  // orphanが存在する場合は最後に挿入
  if (has_orphan) {
    typename Container::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), orphan);
    sorted.insert(pos, orphan);
  }

  return sorted;
}
