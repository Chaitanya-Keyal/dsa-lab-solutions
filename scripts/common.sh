#!/bin/bash
# Common utilities for DSA lab scripts

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Format number with leading zero
fmt_num() { printf "%02d" "$1"; }

# Strip leading zeros from number
strip_num() { echo "$1" | sed 's/^0*//'; }

# Get the latest lab number
get_latest_lab() {
    local latest=$(ls -d labs/lab_* 2>/dev/null | sort -V | tail -1 | sed 's/labs\/lab_//')
    [ -z "$latest" ] && echo "01" || echo "$latest"
}

# Get the latest question number in a lab
get_latest_question() {
    local lab_dir="labs/lab_$(fmt_num "$1")"
    local latest=$(ls "$lab_dir"/question_*.c 2>/dev/null | sort -V | tail -1 | sed 's/.*question_\([0-9]*\)\.c/\1/')
    [ -z "$latest" ] && echo "00" || echo "$latest"
}
