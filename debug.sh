#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/tests/$1`
g++-6 -std=c++11 -O2 -g -Wall -Wextra -Wfatal-errors -Wshadow            \
      -Wconversion -Wfloat-equal -Wlogical-op -Wformat=2 -DLOC           \
      -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2     \
      -fsanitize=address,undefined                                       \
      -o $ROOT/build/tests/$1 $ROOT/tests/$1.cpp
time $ROOT/build/tests/$1
