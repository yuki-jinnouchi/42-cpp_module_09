#!/bin/bash
# Test script for Bitcoin Exchange

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Building Bitcoin Exchange...${NC}"
make && echo -e "${GREEN}Build successful${NC}" || exit 1

test_count=0
pass_count=0

# Test function
run_test() {
    local test_name="$1"
    local input_file="$2"
    local expected_file="$3"

    echo -e "\n${YELLOW}Testing: $test_name${NC}"
    ((test_count++))

    ./btc "$input_file" > temp_output.txt 2>&1

    if diff temp_output.txt "$expected_file" > /dev/null; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((pass_count++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo "Expected:"
        cat "$expected_file"
        echo "Got:"
        cat temp_output.txt
        echo "Diff:"
        diff "$expected_file" temp_output.txt
    fi
    rm -f temp_output.txt
}

# Test no file argument
echo -e "\n${YELLOW}Testing: No file argument${NC}"
((test_count++))
./btc > temp_output.txt 2>&1
if grep -q "could not open file" temp_output.txt; then
    echo -e "${GREEN}✓ PASS${NC}"
    ((pass_count++))
else
    echo -e "${RED}✗ FAIL${NC}"
    echo "Expected error message about file not found"
    cat temp_output.txt
fi
rm -f temp_output.txt

# Test with valid input
run_test "Valid input file" "tests/test_inputs/input.txt" "tests/expected_outputs/expected_output.txt"

echo -e "\n${YELLOW}Results: $pass_count/$test_count tests passed${NC}"

if [ $pass_count -eq $test_count ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi
