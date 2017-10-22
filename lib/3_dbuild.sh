#!/bin/bash
g++ -Wall -Wextra -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -pedantic \
    -Wlogical-op -g -O2 -std=c++11 -o $1.e $1.cpp                          \
    -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC         \
    -fsanitize=address -fsanitize=undefined #-fvisibility=hidden
