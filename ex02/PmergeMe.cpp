#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

#include "CountableInt.hpp"
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
  mergeInsertionSort(_vectorData.begin(), _vectorData.end());
}

// void PmergeMe::sortDeque() {
//   _dequeData = mergeInsertionSort(_dequeData);
// }

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
  mergeInsertionSort(_countableVectorData.begin(), _countableVectorData.end());
}

// void PmergeMe::sortCountableDeque() {
//   _countableDequeData = mergeInsertionSort(_countableDequeData);
// }

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

template <typename iterator>
void PmergeMe::mergeInsertionSort(iterator first, iterator last) {
  typedef typename std::iterator_traits<iterator>::value_type T;

  // Return if the range is empty or has one element
  size_t n = std::distance(first, last);
  if (n <= 1) return;
  // if (n < THRESHOLD) {
  //     insertionSort(first, last);
  //     return;
  // }

  // Make pairs
  std::vector<std::pair<T, T> > pairs = std::vector<std::pair<T, T> >();
  iterator it = first;
  while (std::distance(it, last) >= 2) {
    T a = *it++;
    T b = *it++;
    if (a < b)
      pairs.push_back(std::make_pair(b, a));
    else
      pairs.push_back(std::make_pair(a, b));
  }
  bool hasOrphan = (it != last);
  if (hasOrphan) pairs.push_back(std::make_pair(T(), *it));

  // Make winners and sort them
  std::vector<T> winners = std::vector<T>();
  winners.reserve(pairs.size());
  size_t winners_size = pairs.size();
  if (hasOrphan) winners_size--;
  for (size_t i = 0; i < winners_size; i++) winners.push_back(pairs[i].first);

  // std::cout << "Winners before: " << std::endl;
  // for (size_t i = 0; i < winners.size(); i++) {
  //   std::cout << winners[i] << " ";
  // }
  // std::cout << std::endl;

  mergeInsertionSort(winners.begin(), winners.end());

  // std::cout << "Winners after: " << std::endl;
  // for (size_t i = 0; i < winners.size(); i++) {
  //   std::cout << winners[i] << " ";
  // }
  // std::cout << std::endl;

  // Put winners back to the original range
  iterator originalIt = first;
  typename std::vector<T>::iterator winnerIt;
  for (winnerIt = winners.begin(); winnerIt != winners.end();
       winnerIt++, originalIt++)
    *originalIt = *winnerIt;

  // std::cout << "After putting winners back: " << std::endl;
  // for (iterator it = first; it != last; it++) {
  //   std::cout << *it << " ";
  // }
  // std::cout << std::endl;

  // Put losers back to the original range
  std::vector<size_t> order = Jacobsthal::getInsertionOrder(pairs.size());

  // std::cout << "Losers order:" << std::endl;
  // for (size_t i = 0; i < order.size(); i++) {
  //   std::cout << order[i] << " ";
  // }
  // std::cout << std::endl;

  std::size_t inserted_count = 0;
  for (size_t i = 0; i < order.size(); i++) {
    size_t loser_index = order[i];
    T loser = pairs[loser_index].second;

    iterator search_start = first;
    iterator search_end = first + loser_index + inserted_count;

    iterator pos = std::lower_bound(search_start, search_end, loser);

    // iterator pos = search_start;
    // while(pos != search_end && *pos < loser) {
    //   pos++;
    // }
    // iterator pos = std::lower_bound(search_start, search_end, loser);

    
    // std::cout << "Inserting loser: " << loser << " - "
    //   << "start: " << *search_start << " end: " << *search_end << std::endl;
    // for (iterator it = first; it != originalIt; it++) {
    //   std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // for (iterator it = first; it != last; it++) {
    //   std::cout << *it << " ";
    // }
    // std::cout << std::endl;


    for (iterator shift_it = originalIt; shift_it != pos; shift_it--) {
      *shift_it = *(shift_it - 1);
    }
    *pos = loser;
    originalIt++;
    inserted_count++;


    // std::cout << "Inserted loser: " << loser << " - "
    //   << "start: " << *search_start << " end: " << *search_end << std::endl;
    // for (iterator it = first; it != originalIt; it++) {
    //   std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // for (iterator it = first; it != last; it++) {
    //   std::cout << *it << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;

  }

  // std::cout << "After putting losers back: " << std::endl;
  // for (iterator it = first; it != last; it++) {
  //   std::cout << *it << " ";
  // }
  // std::cout << std::endl;
}
