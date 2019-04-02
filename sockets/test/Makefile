all: test

IFLAGS += -I deps/catch/include 
IFLAGS += -I ../include

test: test.cpp
	g++ -std=c++11 $(IFLAGS) test.cpp -o test.out