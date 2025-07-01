#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
 public:
  // Orthodox Canonical Form
  BitcoinExchange();
  ~BitcoinExchange();

  // Member functions
  bool loadDatabase(const std::string& filename);
  void processInputFile(const std::string& filename);

 private:
  // Orthodox Canonical Form
  BitcoinExchange(const BitcoinExchange& other);
  BitcoinExchange& operator=(const BitcoinExchange& other);

  // Member variables
  std::map<std::string, double> _database;

  // Helper functions
  bool isValidDate(const std::string& date);
  bool isValidRate(const std::string& rate);
  bool isValidValue(const std::string& value);
  double getExchangeRate(const std::string& date);
  void printResult(const std::string& date, double value, double rate);
  void printError(const std::string& message);
};

#endif
