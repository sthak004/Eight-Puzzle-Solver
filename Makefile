STD= --std=c++11

all: 8_puzzle_solver

8_puzzle_solver:
	if [ ! -d bin ]; then mkdir bin; fi
	g++ $(STD) src/8_puzzle_solver.cpp -o bin/8_puzzle_solver


clean:
	rm -rf bin
