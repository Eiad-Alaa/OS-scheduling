all: build

build: main.cpp
	# Use a tab here
	g++ -o main main.cpp

test_output/:
	# Use a tab here
	rm -rf test_output
	mkdir -p test_output

test: build test_output/
	# Use a tab here
	@for file in testcases/*input.txt; do \
		echo "Running test $$file"; \
		basename=$$(basename "$$file" | sed 's/input/output/'); \
		./main < "$$file" > test_output/$$basename; \
	done

	@if diff -r test_output testcases; then \
		echo "All tests passed ya 7amoo "; \
	else \
		echo "Some tests failed ya 7amoo :p"; \
	fi
