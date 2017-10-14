#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/tests/$1`
g++-6 -O2 -Wall -Wextra -std=c++11 -Wl,-stack_size -Wl,16000000 -Wl,-no_pie -o $ROOT/build/tests/$1 $ROOT/tests/$1.cpp
time $ROOT/build/tests/$1
