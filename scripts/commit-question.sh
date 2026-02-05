#!/bin/bash
# Commit a question with pre-commit checks

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.."
source "$SCRIPT_DIR/common.sh"

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

# Allow running directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    commit_question "$@"
fi
