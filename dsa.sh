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
    NUM_TESTS=${3:-2}
    
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

// clang-format off
/* Question:

*/
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
    LAB="$1"
    Q="$2"
    
    # No lab and no question -> run all tests
    if [ -z "$LAB" ] && [ -z "$Q" ]; then
        echo -e "${YELLOW}Running all tests...${NC}"
        echo ""
        for LAB_DIR in lab_*/; do
            [ ! -d "$LAB_DIR" ] && continue
            LAB_NUM=$(basename "$LAB_DIR" | sed 's/lab_//' | sed 's/^0*//')
            for C_FILE in "$LAB_DIR"question_*.c; do
                [ ! -f "$C_FILE" ] && continue
                Q_NUM=$(basename "$C_FILE" .c | sed 's/question_//' | sed 's/^0*//')
                echo -e "${YELLOW}=== Lab $LAB_NUM Question $Q_NUM ===${NC}"
                run_single_test "$LAB_NUM" "$Q_NUM"
                echo ""
            done
        done
        return
    fi
    
    # Question but no lab -> error
    if [ -z "$LAB" ] && [ -n "$Q" ]; then
        echo -e "${RED}Error: Must specify lab when specifying question${NC}"
        exit 1
    fi
    
    # Lab but no question -> run all questions in that lab
    if [ -n "$LAB" ] && [ -z "$Q" ]; then
        LAB=$(printf "%02d" $LAB)
        echo -e "${YELLOW}Running all tests for lab_${LAB}...${NC}"
        echo ""
        for C_FILE in "lab_${LAB}"/question_*.c; do
            [ ! -f "$C_FILE" ] && continue
            Q_NUM=$(basename "$C_FILE" .c | sed 's/question_//' | sed 's/^0*//')
            echo -e "${YELLOW}=== Question $Q_NUM ===${NC}"
            run_single_test "$LAB" "$Q_NUM"
            echo ""
        done
        return
    fi
    
    # Both lab and question -> run single test
    run_single_test "$LAB" "$Q"
}

run_single_test() {
    LAB=$(printf "%02d" $1)
    Q=$(printf "%02d" $2)
    
    C_FILE="lab_${LAB}/question_${Q}.c"
    TEST_DIR="lab_${LAB}/tests/question_${Q}"
    EXECUTABLE="/tmp/dsa_test_$$_${LAB}_${Q}"
    
    if [ ! -f "$C_FILE" ]; then
        echo -e "${RED}File not found: ${C_FILE}${NC}"
        return 1
    fi
    
    gcc -o "$EXECUTABLE" "$C_FILE" -lm 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}Compilation failed!${NC}"
        return 1
    fi
    
    if [ ! -d "$TEST_DIR" ]; then
        echo -e "${YELLOW}No tests found at: ${TEST_DIR}${NC}"
        rm -f "$EXECUTABLE"
        return 1
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
        run_tests "$2" "$3"
        ;;
    *)
        echo "DSA Lab Helper"
        echo ""
        echo "Commands:"
        echo "  ./dsa.sh new <lab> <question> [num_tests]  - Create solution + test files"
        echo "  ./dsa.sh test [lab] [question]             - Run tests"
        echo ""
        echo "Examples:"
        echo "  ./dsa.sh new 1 2 5    # Creates lab_01/question_02.c + 5 test pairs"
        echo "  ./dsa.sh test 1 2     # Runs tests for lab_01/question_02.c"
        echo "  ./dsa.sh test 1       # Runs all tests for lab_01"
        echo "  ./dsa.sh test         # Runs all tests"
        ;;
esac
