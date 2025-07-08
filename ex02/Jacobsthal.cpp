#include "Jacobsthal.hpp"

#include <numeric>

void Jacobsthal::ensureCacheNums(std::size_t n) {
  if (cacheJacobNums.empty()) {
    cacheJacobNums.push_back(0);
    cacheJacobNums.push_back(1);
  }
  for (std::size_t i = cacheJacobNums.size(); i <= n; i++) {
    cacheJacobNums.push_back(cacheJacobNums[i - 1] + 2 * cacheJacobNums[i - 2]);
  }
}

std::size_t Jacobsthal::calcJacobsthal(std::size_t n) {
  ensureCacheNums(n);
  return cacheJacobNums[n];
}

std::vector<std::size_t> Jacobsthal::getSequence(std::size_t n) {
  ensureCacheNums(n + 2);
  std::vector<std::size_t>::iterator start = cacheJacobNums.begin() + 2;
  std::vector<std::size_t>::iterator end = cacheJacobNums.begin() + n + 3;
  return std::vector<std::size_t>(start, end);
}

std::vector<std::size_t> Jacobsthal::getSequenceWithLimit(std::size_t limit) {
  std::size_t temp = 0;

  std::vector<std::size_t> result;
  if (limit == 0) return result;
  for (std::size_t i = 2; temp <= limit ; i++) {
    temp = calcJacobsthal(i);
    result.push_back(temp);
    if (i == 0 && temp > limit)
      return result;
  }
  return result;
}

std::vector<std::size_t> Jacobsthal::getInsertionOrder(std::size_t limit) {
  std::vector<std::size_t> result;
  if (limit == 0) return result;

  std::vector<std::size_t> jacobSizes = getSequenceWithLimit(limit);
  std::size_t start = 0;
  for (std::size_t i = 0; i < jacobSizes.size(); i++) {
    std::size_t end = jacobSizes[i];
    if (end > limit) end = limit;
    for (std::size_t j = end; j > start; j--) {
      result.push_back(j - 1);
    }
    start = end;
    if (start >= limit) break;
  }
  return result;
}
