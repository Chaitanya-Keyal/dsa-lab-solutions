.PHONY: help new test testall commit

MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Support both upper and lowercase
L ?= $(l)
Q ?= $(q)
T ?= $(t)

help:
	@echo "Usage:"
	@echo "  make new               - Create next question in latest lab"
	@echo "  make new l=1 q=2 t=5   - Create lab_01/question_02.c + 5 test pairs"
	@echo "  make test              - Run tests for latest question"
	@echo "  make test l=1 q=2      - Run tests for lab_01/question_02.c"
	@echo "  make test l=1          - Run all tests for lab_01"
	@echo "  make testall           - Run all tests"
	@echo "  make commit            - Commit latest question with pre-commit checks"
	@echo "  make commit l=1 q=2    - Commit lab_01/question_02.c with pre-commit checks"

new:
	@$(MAKEFILE_DIR)scripts/new-solution.sh "$(L)" "$(Q)" "$(T)"

test:
	@$(MAKEFILE_DIR)scripts/run-tests.sh "$(L)" "$(Q)"

testall:
	@$(MAKEFILE_DIR)scripts/run-tests.sh all

commit:
	@$(MAKEFILE_DIR)scripts/commit-question.sh "$(L)" "$(Q)"
