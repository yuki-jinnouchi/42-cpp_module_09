#include <iostream>

#include "BitcoinExchange.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  BitcoinExchange bitcoinExchange;

  // import data.csv file
  if (!bitcoinExchange.loadDatabase("data.csv")) {
    std::cerr << "Error: could not load database." << std::endl;
    return 1;
  }

  // load input.txt
  bitcoinExchange.processInputFile(argv[1]);

  return 0;
}
