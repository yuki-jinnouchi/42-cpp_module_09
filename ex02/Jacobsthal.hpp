#ifndef JACOBSTHAL_HPP
#define JACOBSTHAL_HPP

#include <vector>

class Jacobsthal {
 public:
  static std::size_t calcJacobsthal(std::size_t n);
  static std::vector<std::size_t> getSequence(std::size_t n);
  static std::vector<std::size_t> getSequenceWithLimit(std::size_t limit);
  static std::vector<std::size_t> getInsertionOrder(std::size_t limit);

 private:
  static std::vector<std::size_t> cacheJacobNums;

  static void ensureCacheNums(std::size_t n);
  static void ensureCacheTotalSizes(std::size_t limit_total_size);
};

#endif  // JACOBSTHAL_HPP
