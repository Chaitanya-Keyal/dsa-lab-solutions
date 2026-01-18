#!/bin/bash

# DSA Lab Helper
# Usage:
#   ./dsa.sh new <lab> <question> <num_tests>   - Create solution + test files
#   ./dsa.sh test <lab> <question>              - Run tests

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

new_solution() {
    LAB=$(printf "%02d" $1)
    Q=$(printf "%02d" $2)
    NUM_TESTS=${3:-0}
    
    DIR="lab_${LAB}"
    FILE="${DIR}/question_${Q}.c"
    TEST_DIR="${DIR}/tests/question_${Q}"
    
    # Check if file already exists
    if [ -f "$FILE" ]; then
        echo -e "${YELLOW}Warning: ${FILE} already exists, skipping${NC}"
    else
        mkdir -p "$DIR"
        # Create C file
        cat > "$FILE" << 'EOF'
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    return 0;
}
EOF
        echo -e "${GREEN}Created: ${FILE}${NC}"
    fi
    
    # Create test files (only if they don't exist)
    if [ $NUM_TESTS -gt 0 ]; then
        mkdir -p "$TEST_DIR"
        CREATED=0
        for i in $(seq 1 $NUM_TESTS); do
            NUM=$(printf "%02d" $i)
            if [ ! -f "${TEST_DIR}/input_${NUM}.txt" ]; then
                touch "${TEST_DIR}/input_${NUM}.txt"
                touch "${TEST_DIR}/output_${NUM}.txt"
                CREATED=$((CREATED + 1))
            fi
        done
        
        if [ $CREATED -gt 0 ]; then
            echo -e "${GREEN}Created: ${CREATED} test cases in ${TEST_DIR}${NC}"
        else
            echo -e "${YELLOW}Warning: Test files already exist in ${TEST_DIR}${NC}"
        fi
    fi
}

run_tests() {
    LAB=$(printf "%02d" $1)
    Q=$(printf "%02d" $2)
    
    C_FILE="lab_${LAB}/question_${Q}.c"
    TEST_DIR="lab_${LAB}/tests/question_${Q}"
    EXECUTABLE="/tmp/dsa_test_$$"
    
    if [ ! -f "$C_FILE" ]; then
        echo -e "${RED}File not found: ${C_FILE}${NC}"
        exit 1
    fi
    
    gcc -o "$EXECUTABLE" "$C_FILE" -lm 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}Compilation failed!${NC}"
        exit 1
    fi
    
    if [ ! -d "$TEST_DIR" ]; then
        echo -e "${RED}No tests found at: ${TEST_DIR}${NC}"
        rm -f "$EXECUTABLE"
        exit 1
    fi
    
    PASSED=0; FAILED=0; TOTAL=0
    
    for INPUT_FILE in "$TEST_DIR"/input_*.txt; do
        [ ! -f "$INPUT_FILE" ] && break
        
        TEST_NUM=$(basename "$INPUT_FILE" | sed 's/input_\([0-9]*\)\.txt/\1/')
        OUTPUT_FILE="${TEST_DIR}/output_${TEST_NUM}.txt"
        [ ! -f "$OUTPUT_FILE" ] && continue
        
        TOTAL=$((TOTAL + 1))
        ACTUAL=$("$EXECUTABLE" < "$INPUT_FILE" 2>&1 | sed 's/[[:space:]]*$//')
        EXPECTED=$(cat "$OUTPUT_FILE" | sed 's/[[:space:]]*$//')
        
        if [ "$ACTUAL" = "$EXPECTED" ]; then
            echo -e "${GREEN}✓ Test ${TEST_NUM}${NC}"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ Test ${TEST_NUM}${NC}"
            echo -e "${YELLOW}  Input:${NC}"
            cat "$INPUT_FILE" | sed 's/^/    /'
            echo -e "${YELLOW}  Expected:${NC}"
            echo "$EXPECTED" | sed 's/^/    /'
            echo -e "${YELLOW}  Got:${NC}"
            echo "$ACTUAL" | sed 's/^/    /'
            echo ""
            FAILED=$((FAILED + 1))
        fi
    done
    
    rm -f "$EXECUTABLE"
    echo ""
    echo -e "Results: ${GREEN}${PASSED} passed${NC}, ${RED}${FAILED} failed${NC}, ${TOTAL} total"
}

case "$1" in
    new)
        if [ -z "$2" ] || [ -z "$3" ]; then
            echo "Usage: ./dsa.sh new <lab> <question> [num_tests]"
            echo "Example: ./dsa.sh new 1 2 5"
            exit 1
        fi
        new_solution "$2" "$3" "$4"
        ;;
    test)
        if [ -z "$2" ] || [ -z "$3" ]; then
            echo "Usage: ./dsa.sh test <lab> <question>"
            echo "Example: ./dsa.sh test 1 2"
            exit 1
        fi
        run_tests "$2" "$3"
        ;;
    *)
        echo "DSA Lab Helper"
        echo ""
        echo "Commands:"
        echo "  ./dsa.sh new <lab> <question> <num_tests>  - Create solution + test files"
        echo "  ./dsa.sh test <lab> <question>             - Run tests"
        echo ""
        echo "Examples:"
        echo "  ./dsa.sh new 1 2 5    # Creates lab_01/question_02.c + 5 test pairs"
        echo "  ./dsa.sh test 1 2     # Runs tests for lab_01/question_02.c"
        ;;
esac
