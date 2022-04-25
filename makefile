all: main.cpp
		g++ -fopenmp -Wall -o bin $^
clean:
		rm bin