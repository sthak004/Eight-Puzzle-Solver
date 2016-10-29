all: 8_puzzle_solver

8_puzzle_solver:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ src/8_puzzle_solver.cpp -o bin/8_puzzle_solver


clean:
	rm -rf bin
