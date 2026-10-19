CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

all: wordrank

wordrank: main.cpp rank.hpp database.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o wordrank

test: test.cpp rank.hpp database.hpp
	$(CXX) $(CXXFLAGS) test.cpp -o run_tests
	./run_tests

clean:
	rm -rf wordrank run_tests data_test data
