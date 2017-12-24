#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/tests/$1`
g++-6 -std=c++11 -O2 -g -Wall -Wextra -Wfatal-errors -Wshadow    \
      -Wconversion -Wfloat-equal -Wlogical-op -Wformat=2 -DLOC   \
      -o $ROOT/build/tests/$1 $ROOT/tests/$1.cpp
time $ROOT/build/tests/$1
