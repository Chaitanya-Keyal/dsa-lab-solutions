.PHONY: help new test testall

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

# Create new solution: make new l=1 q=2 t=5
new:
	@./dsa.sh new "$(L)" "$(Q)" "$(T)"

# Run tests: make test l=1 q=2
test:
	@./dsa.sh test "$(L)" "$(Q)"

# Run all tests
testall:
	@./dsa.sh test all
