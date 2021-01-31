#!/bin/bash
set -e
ROOT=`pwd`

mkdir -p `dirname $ROOT/build/$1.e`
g++-10 -std=c++11 -O0 -g -Wall -Wextra -Wfatal-errors -Wshadow            \
       -Wconversion -Wfloat-equal -Wlogical-op -Wformat=2 -DLOC           \
       -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2     \
       -fsanitize=address,undefined -fvisibility=hidden                   \
       -o $ROOT/build/$1.e $ROOT/$1
echo start
time $ROOT/build/$1.e
