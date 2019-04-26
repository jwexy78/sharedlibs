# Overview

A C++ class wrapper for Epoll.

Mimics epoll functionality when it doesn't exist on the system using select.

Note it is currently only build out when epoll does NOT exist.

## Inclusion

Just import ``epoll.h``