#!/bin/bash

OEIS_FILE="./tests/b001768.txt"
BINARY="./PmergeMe"

if [ ! -f "$OEIS_FILE" ]; then
    echo "OEIS file not found: $OEIS_FILE"
    exit 1
fi

if [ -z "$1" ]; then
    echo "Usage: $0 <input_size>"
    exit 1
fi

INPUT_SIZE=$1
if ! [[ "$INPUT_SIZE" =~ ^[0-9]+$ ]]; then
    echo "Input size must be a positive integer."
    exit 1
fi

echo "Input size: $INPUT_SIZE"

MAX_COMPARISONS=$(awk -v n="$INPUT_SIZE" '$1 == n {print $2}' "$OEIS_FILE")

if [ -z "$MAX_COMPARISONS" ]; then
  echo "No OEIS data available for n = $INPUT_SIZE"
  exit 1
fi

echo "Expected maximum comparisons: $MAX_COMPARISONS"
