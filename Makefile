.PHONY: new test help

# Support both upper and lowercase
L ?= $(l)
Q ?= $(q)
T ?= $(t)

# Create new solution: make new l=1 q=2 t=5
new:
	@./dsa.sh new $(L) $(Q) $(T)

# Run tests: make test l=1 q=2
test:
	@./dsa.sh test $(L) $(Q)

help:
	@echo "Usage:"
	@echo "  make new l=1 q=2 t=5   - Create lab_01/question_02.c + 5 test pairs"
	@echo "  make test l=1 q=2      - Run tests for lab_01/question_02.c"
