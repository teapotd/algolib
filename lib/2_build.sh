# UNTESTED
#!/bin/bash
g++ -Wall -Wextra -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -pedantic \
    -Wlogical-op -g -O2 -std=c++11 -o $1.e $1.cpp
