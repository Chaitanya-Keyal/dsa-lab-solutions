# DSA CS F211 - Lab Solutions

Lab solutions for Data Structures and Algorithms (CS F211), 2025-26 Semester 2.

## Quick Start

### Create a new solution

```bash
make new               # Create next question in latest lab
make new l=1 q=2 t=5   # Create lab_01/question_02.c + 5 test pairs
```

Creates a C file with boilerplate and empty test file pairs.

### Run tests

```bash
make test              # Run tests for latest question
make test l=1 q=2      # Run tests for lab_01/question_02.c
make test l=1          # Run all tests for lab_01
make test q=2          # Run question 2 from latest lab
make testall           # Run all tests
```

Compiles and runs against all test cases, showing pass/fail results.

### Commit changes

```bash
make commit            # Commit latest question with pre-commit checks
make commit l=1 q=2    # Commit lab_01/question_02.c with pre-commit checks
```

Runs pre-commit hooks (formatting, trailing whitespace, etc.), then commits the question file and all its test files with message `feat: lab X question Y`. Attempts to sign commits by default, falls back to unsigned if signing fails.

## Test Format

Each test case is a pair of files:

- `input_XX.txt` - Input fed to stdin
- `output_XX.txt` - Expected stdout output
