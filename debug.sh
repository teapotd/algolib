#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/tests/$1`
g++-6 -fvisibility=hidden -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -O2 -Wall -std=c++11 -o $ROOT/build/tests/$1 $ROOT/tests/$1.cpp
time $ROOT/build/tests/$1
