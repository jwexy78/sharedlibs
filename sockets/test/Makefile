SHAREDLIBSROOT = ../..

CC = g++
CFLAGS = -std=c++11

include ../rules.mk
include $(SHAREDLIBSROOT)/catch/rules.mk

all: test

test: test.cpp
	$(CC) $(CFLAGS) $(IFLAGS) test.cpp -o test.out