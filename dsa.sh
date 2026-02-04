#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

cd "$(dirname "$0")"

fmt_num() { printf "%02d" "$1"; }
strip_num() { echo "$1" | sed 's/^0*//'; }

get_latest_lab() {
    local latest=$(ls -d labs/lab_* 2>/dev/null | sort -V | tail -1 | sed 's/labs\/lab_//')
    [ -z "$latest" ] && echo "01" || echo "$latest"
}

get_latest_question() {
    local lab_dir="labs/lab_$(fmt_num "$1")"
    local latest=$(ls "$lab_dir"/question_*.c 2>/dev/null | sort -V | tail -1 | sed 's/.*question_\([0-9]*\)\.c/\1/')
    [ -z "$latest" ] && echo "00" || echo "$latest"
}

print_summary() {
    local passed=$1 failed=$2
    echo -e "${YELLOW}================================${NC}"
    echo -e "${YELLOW}FINAL SUMMARY${NC}"
    echo -e "${GREEN}${passed} passed${NC}, ${RED}${failed} failed${NC}"
}

new_solution() {
    local lab="$1" q="$2" num_tests=${3:-2}

    [ -z "$lab" ] && lab=$(strip_num "$(get_latest_lab)")
    [ -z "$q" ] && q=$(($(strip_num "$(get_latest_question "$lab")") + 1))

    lab=$(fmt_num "$lab")
    q=$(fmt_num "$q")
    local dir="labs/lab_${lab}"
    local file="${dir}/question_${q}.c"
    local test_dir="${dir}/tests/question_${q}"

    if [ -f "$file" ]; then
        echo -e "${YELLOW}Warning: ${file} already exists, skipping${NC}"
    else
        mkdir -p "$dir"
        cp template.c "$file"
        echo -e "${GREEN}Created: ${file}${NC}"
    fi

    [ "$num_tests" -le 0 ] && return

    mkdir -p "$test_dir"
    local created=0
    for i in $(seq 1 "$num_tests"); do
        local num=$(fmt_num "$i")
        if [ ! -f "${test_dir}/input_${num}.txt" ]; then
            touch "${test_dir}/input_${num}.txt" "${test_dir}/output_${num}.txt"
            ((created++))
        fi
    done

    if [ "$created" -gt 0 ]; then
        echo -e "${GREEN}Created: ${created} test cases in ${test_dir}${NC}"
    else
        echo -e "${YELLOW}Warning: Test files already exist in ${test_dir}${NC}"
    fi
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
        # Only lab given: run all tests for that lab
        local lab_fmt=$(fmt_num "$lab")
        run_multi_tests "labs/lab_${lab_fmt}/question_*.c" "Running all tests for Lab ${lab_fmt}..."
    else
        # Default lab/q to latest if not given
        [ -z "$lab" ] && lab=$(strip_num "$(get_latest_lab)")
        [ -z "$q" ] && q=$(strip_num "$(get_latest_question "$lab")")
        [ "$q" = "0" ] && { echo -e "${RED}No questions found${NC}"; exit 1; }
        run_single_test "$lab" "$q"
    fi
}

commit_question() {
    local lab="$1" q="$2"

    [ -z "$lab" ] && lab=$(strip_num "$(get_latest_lab)")
    [ -z "$q" ] && q=$(strip_num "$(get_latest_question "$lab")")

    local lab_fmt=$(fmt_num "$lab")
    local q_fmt=$(fmt_num "$q")
    local question_file="labs/lab_${lab_fmt}/question_${q_fmt}.c"
    local test_dir="labs/lab_${lab_fmt}/tests/question_${q_fmt}"

    echo -e "${YELLOW}Committing Lab ${lab} Question ${q}...${NC}"

    if [ ! -f "$question_file" ]; then
        echo -e "${RED}Error: ${question_file} not found${NC}"
        return 1
    fi

    echo -e "${YELLOW}Running pre-commit checks...${NC}"
    pre-commit run --files "$question_file" "$test_dir"/* 2>/dev/null || true

    git add "$question_file" "$test_dir" 2>/dev/null || true

    if git diff --cached --quiet; then
        echo -e "${YELLOW}No changes to commit${NC}"
        return 0
    fi

    if git commit -S -m "feat: lab $lab question $q" 2>/dev/null; then
        echo -e "${GREEN}✓ Committed with signature${NC}"
    else
        echo -e "${YELLOW}Signing failed, committing without signature...${NC}"
        git commit -m "feat: lab $lab question $q"
        echo -e "${GREEN}✓ Committed without signature${NC}"
    fi
}

case "$1" in
    new)
        new_solution "$2" "$3" "$4"
        ;;
    test)
        run_tests "$2" "$3"
        ;;
    commit)
        commit_question "$2" "$3"
        ;;
    *)
        cat << 'EOF'
DSA Lab Helper

Commands:
  ./dsa.sh new [lab] [question] [num_tests]  - Create solution + test files
  ./dsa.sh test [lab] [question]             - Run tests
  ./dsa.sh test all                          - Run all tests
  ./dsa.sh commit [lab] [question]           - Commit with pre-commit checks

Examples:
  ./dsa.sh new           # Creates next question in latest lab
  ./dsa.sh new 1 2 5     # Creates labs/lab_01/question_02.c + 5 test pairs
  ./dsa.sh test          # Runs tests for latest question
  ./dsa.sh test 1 2      # Runs tests for labs/lab_01/question_02.c
  ./dsa.sh test 1        # Runs all tests for lab_01
  ./dsa.sh test all      # Runs all tests
  ./dsa.sh commit        # Commits latest question
  ./dsa.sh commit 1 2    # Commits labs/lab_01/question_02.c
EOF
        ;;
esac
