#!/bin/bash
# Test script for RPN

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Build the project
echo -e "${YELLOW}Building RPN...${NC}"
if ! make; then
    echo -e "${RED}Build failed. Please check the Makefile or source code for errors.${NC}"
    exit 1
fi
echo -e "${GREEN}Build successful${NC}"

test_count=0
pass_count=0

# Test function
run_test() {
    local test_name="$1"
    local input="$2"
    local expected="$3"

    echo "Testing: $test_name"
    echo "Input: $input"
    ((test_count++))

    if [ "$expected" = "Error" ]; then
        # Test for error case
        ./RPN "$input" > temp_output.txt 2>&1
        if grep -q "Error" temp_output.txt; then
            echo -e "${GREEN}✓ PASS (Error detected as expected)${NC}"
            ((pass_count++))
        else
            echo -e "${RED}✗ FAIL (Expected error but got different output)${NC}"
            echo "Output:"
            cat temp_output.txt
        fi
    else
        # Test for normal case
        output=$(./RPN "$input" 2>&1)
        if [ "$output" = "$expected" ]; then
            echo -e "${GREEN}✓ PASS (Output matches expected: $output)${NC}"
            ((pass_count++))
        else
            echo -e "${RED}✗ FAIL${NC}"
            echo "Expected: $expected"
            echo "Got: $output"
        fi
    fi
    rm -f temp_output.txt
    echo
}

# Determine the directory of this script
script_dir=$(dirname "$(realpath "$0")")

# Read test cases from test_cases.txt
test_cases_file="$script_dir/test_cases.txt"
if [ ! -f "$test_cases_file" ]; then
    echo -e "${RED}Test cases file not found: $test_cases_file${NC}"
    exit 1
fi

echo -e "${YELLOW}Running test cases from $test_cases_file...${NC}"
while IFS="," read -r input expected; do
    # Skip comments and empty lines
    if [[ "$input" =~ ^#.*$ || -z "$input" ]]; then
        continue
    fi

    # Remove leading/trailing whitespace and clean up input/expected
    input=$(echo "$input" | sed 's/^ *//;s/ *$//')
    expected=$(echo "$expected" | sed 's/^ *//;s/ *$//')

    # Run the test
    run_test "Test case: $input" "$input" "$expected"
done < "$test_cases_file"

echo -e "${YELLOW}Results: $pass_count/$test_count tests passed${NC}"

if [ $pass_count -eq $test_count ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed.${NC}"
    exit 1
fi
