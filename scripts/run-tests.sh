#!/bin/bash
# Run tests for DSA lab solutions

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."
source "$SCRIPT_DIR/common.sh"

# Shared variables for test counts
PASSED=0
FAILED=0

print_summary() {
    local passed=$1 failed=$2
    echo -e "${YELLOW}================================${NC}"
    echo -e "${YELLOW}FINAL SUMMARY${NC}"
    echo -e "${GREEN}${passed} passed${NC}, ${RED}${failed} failed${NC}"
}

run_single_test() {
    local lab=$(fmt_num "$1") q=$(fmt_num "$2")
    local c_file="labs/lab_${lab}/question_${q}.c"
    local test_dir="labs/lab_${lab}/tests/question_${q}"
    local exe="/tmp/dsa_test_$$_${lab}_${q}"

    echo -e "${YELLOW}=== Lab ${lab} Question ${q} ===${NC}"
    PASSED=0 FAILED=0

    if [ ! -f "$c_file" ]; then
        echo -e "${RED}File not found: ${c_file}${NC}"
        return 1
    fi

    if ! gcc -o "$exe" "$c_file" -lm 2>&1; then
        echo -e "${RED}Compilation failed!${NC}"
        return 1
    fi

    if [ ! -d "$test_dir" ]; then
        echo -e "${YELLOW}No tests found at: ${test_dir}${NC}"
        rm -f "$exe"
        return 1
    fi

    for input_file in "$test_dir"/input_*.txt; do
        [ ! -f "$input_file" ] && break

        local test_num=$(basename "$input_file" | sed 's/input_\([0-9]*\)\.txt/\1/')
        local output_file="${test_dir}/output_${test_num}.txt"
        [ ! -f "$output_file" ] && continue
        local actual=$("$exe" < "$input_file" 2>&1 | sed 's/[[:space:]]*$//')
        local expected=$(sed 's/[[:space:]]*$//' "$output_file")

        if [ "$actual" = "$expected" ]; then
            echo -e "${GREEN}✓ Test ${test_num}${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✗ Test ${test_num}${NC}"
            echo -e "${YELLOW}  Input:${NC}"
            sed 's/^/    /' "$input_file"
            echo -e "${YELLOW}  Expected:${NC}"
            echo "$expected" | sed 's/^/    /'
            echo -e "${YELLOW}  Got:${NC}"
            echo "$actual" | sed 's/^/    /'
            echo ""
            ((FAILED++))
        fi
    done

    rm -f "$exe"
    echo -e "${GREEN}${PASSED} passed${NC}, ${RED}${FAILED} failed${NC}"
    [ "$FAILED" -eq 0 ]
}

run_multi_tests() {
    local lab_pattern="$1" header="$2"
    local total_passed=0 total_failed=0

    echo -e "${YELLOW}${header}${NC}"
    echo ""

    for c_file in $lab_pattern; do
        [ ! -f "$c_file" ] && continue
        local lab_num=$(strip_num "$(basename "$(dirname "$c_file")" | sed 's/labs\/lab_//' | sed 's/lab_//')")
        local q_num=$(strip_num "$(basename "$c_file" .c | sed 's/question_//')")

        run_single_test "$lab_num" "$q_num"
        ((total_passed += PASSED))
        ((total_failed += FAILED))
        echo ""
    done

    print_summary "$total_passed" "$total_failed"
    [ "$total_failed" -eq 0 ]
}

run_tests() {
    local lab="$1" q="$2"

    if [ "$lab" = "all" ]; then
        run_multi_tests "labs/lab_*/question_*.c" "Running all tests..."
    elif [ -z "$q" ] && [ -n "$lab" ]; then
        local lab_fmt=$(fmt_num "$lab")
        run_multi_tests "labs/lab_${lab_fmt}/question_*.c" "Running all tests for Lab ${lab_fmt}..."
    else
        [ -z "$lab" ] && lab=$(strip_num "$(get_latest_lab)")
        [ -z "$q" ] && q=$(strip_num "$(get_latest_question "$lab")")
        [ "$q" = "0" ] && { echo -e "${RED}No questions found${NC}"; exit 1; }
        run_single_test "$lab" "$q"
    fi
}

# Allow running directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    run_tests "$@"
fi
