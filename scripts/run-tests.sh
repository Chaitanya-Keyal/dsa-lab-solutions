#!/bin/bash
# Run tests for DSA lab solutions

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."
source "$SCRIPT_DIR/common.sh"

# Parallel execution settings
MAX_JOBS=${MAX_JOBS:-$(nproc 2>/dev/null || echo 4)}
RESULTS_DIR="/tmp/dsa_test_results_$$"
mkdir -p "$RESULTS_DIR"
SEPARATOR="${YELLOW}================================${NC}"

print_summary() {
    local passed=$1 failed=$2
    echo -e "$SEPARATOR"
    echo -e "${YELLOW}FINAL SUMMARY${NC}"
    if [ "$failed" -eq 0 ]; then
        echo -e "${GREEN}${passed} passed${NC}, ${RED}${failed} failed${NC}"
    else
        echo -e "${RED}${passed} passed, ${failed} FAILED${NC}"
    fi
}

show_failed_tests() {
    local has_failures=false

    for result_file in "$RESULTS_DIR"/*.result; do
        [ ! -f "$result_file" ] && continue
        read passed failed < "$result_file"

        if [ "$failed" -gt 0 ]; then
            has_failures=true
            break
        fi
    done

    if [ "$has_failures" = true ]; then
        echo -e "\n${RED}Failed Tests Details:${NC}"
        echo -e "$SEPARATOR"

        for result_file in "$RESULTS_DIR"/*.result; do
            [ ! -f "$result_file" ] && continue
            read passed failed < "$result_file"

            if [ "$failed" -gt 0 ]; then
                local test_id=$(basename "$result_file" .result)
                local output_file="$RESULTS_DIR/${test_id}.output"
                if [ -f "$output_file" ]; then
                    cat "$output_file"
                fi
            fi
        done

        echo -e "$SEPARATOR\n"
    fi
}

acquire_semaphore() {
    while [ "$(jobs -r | wc -l)" -ge "$MAX_JOBS" ]; do
        sleep 0.1
    done
}

run_single_test() {
    local lab=$(fmt_num "$1") q=$(fmt_num "$2")
    local c_file="labs/lab_${lab}/question_${q}.c"
    local test_dir="labs/lab_${lab}/tests/question_${q}"
    local exe="/tmp/dsa_test_$$_${lab}_${q}"
    local result_file="$RESULTS_DIR/${lab}_${q}.result"
    local output_file="$RESULTS_DIR/${lab}_${q}.output"

    {
        echo -e "${YELLOW}=== Lab ${lab} Question ${q} ===${NC}"
        PASSED=0 FAILED=0

        if [ ! -f "$c_file" ]; then
            echo -e "${RED}File not found: ${c_file}${NC}"
            echo "0 1" > "$result_file"
            exit 1
        fi

        if ! gcc -o "$exe" "$c_file" -lm 2>&1; then
            echo -e "${RED}Compilation failed!${NC}"
            echo "0 1" > "$result_file"
            exit 1
        fi

        if [ ! -d "$test_dir" ]; then
            echo -e "${YELLOW}No tests found at: ${test_dir}${NC}"
            rm -f "$exe"
            echo "0 0" > "$result_file"
            exit 0
        fi

        for input_file in "$test_dir"/input_*.txt; do
            [ ! -f "$input_file" ] && break

            local test_num=$(basename "$input_file" | sed 's/input_\([0-9]*\)\.txt/\1/')
            local output_test="${test_dir}/output_${test_num}.txt"
            [ ! -f "$output_test" ] && continue
            local actual=$("$exe" < "$input_file" 2>&1 | sed 's/[[:space:]]*$//')
            local expected=$(sed 's/[[:space:]]*$//' "$output_test")

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
        if [ "$FAILED" -eq 0 ]; then
            echo -e "${GREEN}${PASSED} passed${NC}, ${RED}${FAILED} failed${NC}"
        else
            echo -e "${RED}${PASSED} passed, ${FAILED} FAILED${NC}"
        fi
        echo ""
        echo "$PASSED $FAILED" > "$result_file"
    } > "$output_file" 2>&1
}

run_multi_tests() {
    local lab_pattern="$1" header="$2"
    local total_passed=0 total_failed=0
    local pids=()
    local test_order=()
    local test_count=0

    echo -e "${YELLOW}${header}${NC}"
    echo ""

    # Count total tests first
    for c_file in $lab_pattern; do
        [ ! -f "$c_file" ] && continue
        ((test_count++))
    done

    local current_test=0
    for c_file in $lab_pattern; do
        [ ! -f "$c_file" ] && continue
        local lab_num=$(strip_num "$(basename "$(dirname "$c_file")" | sed 's/labs\/lab_//' | sed 's/lab_//')")
        local q_num=$(strip_num "$(basename "$c_file" .c | sed 's/question_//')")

        ((current_test++))
        echo -ne "\rRunning tests... ($current_test/$test_count)  " >&2

        # Acquire semaphore before starting new job
        acquire_semaphore

        # Run test in background
        run_single_test "$lab_num" "$q_num" &
        pids+=($!)
        test_order+=("${lab_num}_${q_num}")
    done

    # Wait for all background jobs to complete
    for pid in "${pids[@]}"; do
        wait "$pid"
    done

    echo -ne "\r" >&2

    # Display all captured output in order
    for test_id in "${test_order[@]}"; do
        local output_file="$RESULTS_DIR/${test_id}.output"
        if [ -f "$output_file" ]; then
            cat "$output_file"
        fi
    done

    # Aggregate results from all test files
    for result_file in "$RESULTS_DIR"/*.result; do
        [ ! -f "$result_file" ] && continue
        read passed failed < "$result_file"
        ((total_passed += passed))
        ((total_failed += failed))
    done

    show_failed_tests
    print_summary "$total_passed" "$total_failed"

    rm -rf "$RESULTS_DIR"
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

        # Run single test and display output
        local lab_fmt=$(fmt_num "$lab") q_fmt=$(fmt_num "$q")
        run_single_test "$lab" "$q"

        # Display output file
        local output_file="$RESULTS_DIR/${lab_fmt}_${q_fmt}.output"
        if [ -f "$output_file" ]; then
            cat "$output_file"
        fi

        # Clean up
        rm -rf "$RESULTS_DIR"
    fi
}


# Allow running directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    run_tests "$@"
fi
