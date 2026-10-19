CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

all: wordrank

wordrank: src/main.cpp src/rank.hpp src/database.hpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o wordrank

test: tests/test.cpp src/rank.hpp src/database.hpp
	$(CXX) $(CXXFLAGS) tests/test.cpp -o run_tests
	./run_tests

clean:
	rm -rf wordrank run_tests data_test
