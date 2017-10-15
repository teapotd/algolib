#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/tests/$1`
g++-6 -Wall -Wextra -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -pedantic \
      -fsanitize=address -fsanitize=undefined -D_FORTIFY_SOURCE=2            \
      -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fvisibility=hidden         \
      -Wlogical-op -O2 -std=c++11 -o $ROOT/build/tests/$1 $ROOT/tests/$1.cpp
time $ROOT/build/tests/$1
