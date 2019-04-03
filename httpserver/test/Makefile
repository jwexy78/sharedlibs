SHAREDLIBSROOT = ../..

CC = g++
CFLAGS = -std=c++11

include ../rules.mk
include ../../catch/rules.mk

all: test

test:
	$(CC) $(CFLAGS) $(IFLAGS) test.cpp -o test.out