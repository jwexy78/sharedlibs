# Rules file to be included in any file
# using this library.

ifndef SHAREDLIBSROOT
SHAREDLIBSROOT=../..
endif

include $(SHAREDLIBSROOT)/sockets/rules.mk

IFLAGS += -I $(SHAREDLIBSROOT)/httpserver/include

