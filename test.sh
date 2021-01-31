#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/$1.e`
g++-10 -std=c++11 -O2 -g -Wall -Wextra -Wfatal-errors -Wshadow    \
       -Wconversion -Wfloat-equal -Wlogical-op -Wformat=2 -DLOC   \
       -Wl,-stack_size -Wl,0x10000000 \
       -o $ROOT/build/$1.e $ROOT/$1
echo start
time $ROOT/build/$1.e
