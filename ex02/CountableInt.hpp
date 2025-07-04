#ifndef COUNTABLEINT_HPP
#define COUNTABLEINT_HPP

class CountableInt {
 public:
  // static variable to count comparisons
  static int _comparison_count;

  // Orthodox Canonical Form
  CountableInt();
  CountableInt(int value);
  ~CountableInt();
  CountableInt(const CountableInt &other);
  CountableInt &operator=(const CountableInt &other);

  // Overloaded operators for comparison
  bool operator<(const CountableInt &other) const;
  bool operator>(const CountableInt &other) const;
  bool operator<=(const CountableInt &other) const;
  bool operator>=(const CountableInt &other) const;
  bool operator==(const CountableInt &other) const;
  bool operator!=(const CountableInt &other) const;

  // Accessor methods
  int getValue() const;
  operator int() const;

  // Static methods
  static void resetCount();
  static int getComparisonCount();

 private:
  int _value;
};

#endif  // COUNTABLEINT_HPP
