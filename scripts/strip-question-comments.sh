#!/bin/bash
# Pre-commit hook to remove the question comment section from C files
# Removes everything from "// clang-format off" to the end of the file
# Exits with 1 if files were modified, 0 if no changes needed

modified=0

for file in "$@"; do
    if [[ -f "$file" ]]; then
        # Find the line number where "// clang-format off" appears
        line_num=$(grep -n "^// clang-format off$" "$file" | head -1 | cut -d: -f1)

        if [[ -n "$line_num" ]]; then
            # Keep only lines before the clang-format off comment
            head -n $((line_num - 1)) "$file" > "$file.tmp"
            mv "$file.tmp" "$file"
            echo "Stripped question comments from: $file"
            modified=1
        fi
    fi
done

exit $modified
