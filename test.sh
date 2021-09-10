#!/bin/bash
set -e
ROOT=`pwd`

if [ $# -lt 2 ]; then
    echo "usage: ./test.sh [b|d] [path to cpp file] [arguments...]"
    exit 1
fi

FLAGS="-std=c++11 -DLOC -Wl,-stack_size -Wl,0x10000000"
FLAGS+=" -Wall -Wextra -Wfatal-errors -Wshadow -Wlogical-op -Wconversion -Wfloat-equal"
FLAGS+=" -Wformat=2 -Wcast-qual -Wcast-align -Wduplicated-cond"

if [ $1 = "b" ]; then
	FLAGS+=" -O2"
elif [ $1 = "d" ]; then
	FLAGS+=" -O0 -g -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address,undefined -fvisibility=hidden"
else
    echo "usage: ./test.sh [b|d] [path to cpp file] [arguments...]"
    exit 1
fi

SRC=$ROOT/$2
EXE=$ROOT/build/$2.e

mkdir -p `dirname $EXE`
g++-11 $FLAGS -o $EXE $SRC
echo start
time $EXE ${@:3}
