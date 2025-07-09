#include "PmergeMe.hpp"

#include <algorithm>
#include <cstddef>
#include <deque>
#include <iostream>
// #include <map>
#include <vector>
// #include <unordered_map>

#include "CountableInt.hpp"
#include "IndexedValue.hpp"
#include "Jacobsthal.hpp"

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
  std::vector<IndexedValue<int> > pairs = std::vector<IndexedValue<int> >();
  for (size_t i = 0; i < _vectorData.size(); i++) {
    IndexedValue<int> pair(_vectorData[i], 0);
    pairs.push_back(pair);
  }
  mergeInsertionSortVec(pairs.begin(), pairs.end());
  for (size_t i = 0; i < pairs.size(); i++) {
    _vectorData[i] = pairs[i]._value;
  }
}

void PmergeMe::sortDeque() {
  std::deque<IndexedValue<int> > pairs =
      std::deque<IndexedValue<int> >();
  for (size_t i = 0; i < _dequeData.size(); i++) {
    IndexedValue<int> pair(_dequeData[i], 0);
    pairs.push_back(pair);
  }
  mergeInsertionSortDeque(pairs.begin(), pairs.end());
  for (size_t i = 0; i < pairs.size(); i++) {
    _dequeData[i] = pairs[i]._value;
  }
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
  std::vector<IndexedValue<CountableInt> > pairs =
      std::vector<IndexedValue<CountableInt> >();

  for (size_t i = 0; i < _vectorData.size(); i++) {
    IndexedValue<CountableInt> pair(_vectorData[i], 0);
    pairs.push_back(pair);
  }

  // printVector(pairs, "Before sorting: ");

  mergeInsertionSortVec(pairs.begin(), pairs.end());

  for (size_t i = 0; i < pairs.size(); i++) {
    _countableVectorData[i] = pairs[i]._value;
  }
}

void PmergeMe::sortCountableDeque() {
  std::deque<IndexedValue<CountableInt> > pairs =
      std::deque<IndexedValue<CountableInt> >();

  for (size_t i = 0; i < _dequeData.size(); i++) {
    IndexedValue<CountableInt> pair(_dequeData[i], 0);
    pairs.push_back(pair);
  }

  // printVector(pairs, "Before sorting: ");

  mergeInsertionSortDeque(pairs.begin(), pairs.end());

  for (size_t i = 0; i < pairs.size(); i++) {
    _countableDequeData[i] = pairs[i]._value;
  }
}

void PmergeMe::printComparisonCounts() const {
  std::cout << "count : " << CountableInt::getComparisonCount() << std::endl;
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

  std::cout << "Countable Deque data: ";
  for (std::deque<CountableInt>::const_iterator it =
           _countableDequeData.begin();
       it != _countableDequeData.end(); ++it) {
    CountableInt item = *it;
    std::cout << item.getValue() << " ";
  }
  std::cout << std::endl;
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

  // Check if deque is sorted
  temp = 0;
  for (std::deque<CountableInt>::const_iterator it =
           _countableDequeData.begin();
       it != _countableDequeData.end(); it++) {
    CountableInt item = *it;
    if (temp > item.getValue()) return false;
    temp = item.getValue();
  }

  return true;
}

// Vector
template <typename T>
std::pair<std::vector<T>, std::vector<T> > PmergeMe::extract(
    typename std::vector<T>::iterator first,
    typename std::vector<T>::iterator last) {
  typedef typename std::vector<T>::iterator iterator;

  std::vector<T> winners;
  std::vector<T> losers;

  size_t index = 0;
  iterator it = first;
  while (std::distance(it, last) >= 2) {
    T a = *it++;
    a.pushIndex(index);
    T b = *it++;
    b.pushIndex(index);
    if (a > b) {
      winners.push_back(a);
      losers.push_back(b);
    } else {
      winners.push_back(b);
      losers.push_back(a);
    }
    index++;
  }

  bool hasOrphan = (it != last);
  if (hasOrphan) {
    T orphan = *it;
    orphan.pushIndex(index);
    losers.push_back(orphan);
  }

  std::pair<std::vector<T>, std::vector<T> > pairs;
  pairs.first = winners;
  pairs.second = losers;
  return pairs;
}

template <typename T>
void PmergeMe::popIndexes(std::vector<T> &vec) {
  for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();
       it++) {
    T &item = *it;
    item.popIndex();
  }
}

template <typename T>
std::vector<T> PmergeMe::mergeVectors(std::vector<T> &winners,
                                      std::vector<T> &losers) {
  typedef typename std::vector<T>::iterator iterator;

  std::vector<T> merged;

  merged.reserve(winners.size() + losers.size());
  for (size_t i = 0; i < winners.size(); i++) {
    merged.push_back(winners[i]);
  }

  // printVector(merged, "Merge_before:");

  std::vector<size_t> schedule;
  schedule = Jacobsthal::getInsertionOrder(losers.size());

  // printVector(schedule, "Schedule:");

  size_t inserted_count = 0;
  for (size_t i = 0; i < schedule.size(); i++) {
    T loser;
    size_t schedule_index = schedule[i];

    if (winners.size() != losers.size() && schedule_index == winners.size()) {
      loser = losers[schedule_index];
    } else {
      size_t common_index = winners[schedule_index].getIndex();
      size_t loser_index;
      for (loser_index = 0; loser_index < losers.size(); loser_index++) {
        if (losers[loser_index].getIndex() == common_index) {
          loser = losers[loser_index];
          break;
        }
      }
    }

    iterator search_start = merged.begin();
    iterator search_end = merged.begin() + schedule_index + inserted_count;
    iterator pos = std::lower_bound(search_start, search_end, loser);
    if (pos == merged.end()) {
      merged.push_back(loser);
    } else {
      merged.insert(pos, loser);
    }
    inserted_count++;
  }
  return merged;
}

template <typename T>
void PmergeMe::printVector(std::vector<T> &vec, std::string explain) const {
  // show text with padding
  std::cout << explain << std::string(18 - explain.size(), ' ');
  for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();
       ++it) {
    std::cout << *it << " ";
  }
}

template <typename iterator>
void PmergeMe::mergeInsertionSortVec(iterator first, iterator last) {
  // Return if the range is empty or has one element
  size_t n = std::distance(first, last);
  if (n <= 1) return;

  typedef typename std::iterator_traits<iterator>::value_type T;

  std::pair<std::vector<T>, std::vector<T> > pairs = extract<T>(first, last);

  std::vector<T> winners = pairs.first;
  std::vector<T> winners_copy = winners;  // for debug
  std::vector<T> losers = pairs.second;

  mergeInsertionSortVec(winners.begin(), winners.end());

  std::vector<T> mergerd = mergeVectors(winners, losers);

  // printVector(winners_copy, std::string("Winners_before:"));
  // printVector(winners, std::string("Winners_after:"));
  // printVector(losers, std::string("Losers:"));
  // printVector(mergerd, "Merged:");

  popIndexes(mergerd);

  // std::cout << std::endl;

  std::copy(mergerd.begin(), mergerd.end(), first);
}


// Deque
template <typename T>
std::pair<std::deque<T>, std::deque<T> > PmergeMe::extract(
    typename std::deque<T>::iterator first,
    typename std::deque<T>::iterator last) {
  typedef typename std::deque<T>::iterator iterator;

  std::deque<T> winners;
  std::deque<T> losers;

  size_t index = 0;
  iterator it = first;
  while (std::distance(it, last) >= 2) {
    T a = *it++;
    a.pushIndex(index);
    T b = *it++;
    b.pushIndex(index);
    if (a > b) {
      winners.push_back(a);
      losers.push_back(b);
    } else {
      winners.push_back(b);
      losers.push_back(a);
    }
    index++;
  }

  bool hasOrphan = (it != last);
  if (hasOrphan) {
    T orphan = *it;
    orphan.pushIndex(index);
    losers.push_back(orphan);
  }

  std::pair<std::deque<T>, std::deque<T> > pairs;
  pairs.first = winners;
  pairs.second = losers;
  return pairs;
}

template <typename T>
void PmergeMe::popIndexes(std::deque<T> &vec) {
  for (typename std::deque<T>::iterator it = vec.begin(); it != vec.end();
       it++) {
    T &item = *it;
    item.popIndex();
  }
}

template <typename T>
std::deque<T> PmergeMe::mergeVectors(std::deque<T> &winners,
                                      std::deque<T> &losers) {
  typedef typename std::deque<T>::iterator iterator;

  std::deque<T> merged;

  // merged.reserve(winners.size() + losers.size());
  for (size_t i = 0; i < winners.size(); i++) {
    merged.push_back(winners[i]);
  }

  // printVector(merged, "Merge_before:");

  std::vector<size_t> schedule;
  schedule = Jacobsthal::getInsertionOrder(losers.size());

  // printVector(schedule, "Schedule:");

  size_t inserted_count = 0;
  for (size_t i = 0; i < schedule.size(); i++) {
    T loser;
    size_t schedule_index = schedule[i];

    if (winners.size() != losers.size() && schedule_index == winners.size()) {
      loser = losers[schedule_index];
    } else {
      size_t common_index = winners[schedule_index].getIndex();
      size_t loser_index;
      for (loser_index = 0; loser_index < losers.size(); loser_index++) {
        if (losers[loser_index].getIndex() == common_index) {
          loser = losers[loser_index];
          break;
        }
      }
    }

    iterator search_start = merged.begin();
    iterator search_end = merged.begin() + schedule_index + inserted_count;
    iterator pos = std::lower_bound(search_start, search_end, loser);
    if (pos == merged.end()) {
      merged.push_back(loser);
    } else {
      merged.insert(pos, loser);
    }
    inserted_count++;
  }
  return merged;
}

template <typename T>
void PmergeMe::printVector(std::deque<T> &vec, std::string explain) const {
  // show text with padding
  std::cout << explain << std::string(18 - explain.size(), ' ');
  for (typename std::deque<T>::iterator it = vec.begin(); it != vec.end();
       ++it) {
    std::cout << *it << " ";
  }
}

template <typename iterator>
void PmergeMe::mergeInsertionSortDeque(iterator first, iterator last) {
  // Return if the range is empty or has one element
  size_t n = std::distance(first, last);
  if (n <= 1) return;

  typedef typename std::iterator_traits<iterator>::value_type T;

  std::pair<std::deque<T>, std::deque<T> > pairs = extract<T>(first, last);

  std::deque<T> winners = pairs.first;
  std::deque<T> winners_copy = winners;  // for debug
  std::deque<T> losers = pairs.second;

  mergeInsertionSortDeque(winners.begin(), winners.end());

  std::deque<T> mergerd = mergeVectors(winners, losers);

  // printVector(winners_copy, std::string("Winners_before:"));
  // printVector(winners, std::string("Winners_after:"));
  // printVector(losers, std::string("Losers:"));
  // printVector(mergerd, "Merged:");

  popIndexes(mergerd);

  // std::cout << std::endl;

  std::copy(mergerd.begin(), mergerd.end(), first);
}


