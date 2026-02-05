#!/bin/bash
# Create new solution and test files

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."
source "$SCRIPT_DIR/common.sh"

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

# Allow running directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    new_solution "$@"
fi
