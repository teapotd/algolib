#!/bin/bash
set -e
ROOT=`pwd`

if [ $# -ne 2 ]; then
	echo "usage: ./build.sh [b|d|c] [path to cpp file]"
	exit 1
fi

FLAGS="-std=c++20 -DLOC"
FLAGS+=" -Wall -W -Wfatal-errors -Wshadow -Wlogical-op -Wconversion -Wfloat-equal"
FLAGS+=" -Wformat=2 -Wcast-qual -Wcast-align -Wduplicated-cond"
FLAGS+=" -Wno-misleading-indentation"

if [[ $OSTYPE == 'darwin'* ]]; then
	FLAGS+=" -Wl,-stack_size -Wl,0x10000000 -fvisibility=hidden"
fi

if [ $1 = "b" ]; then
	FLAGS+=" -O2"
elif [ $1 = "d" ]; then
	FLAGS+=" -O0 -g -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address,undefined"
elif [ $1 = "c" ]; then
	FLAGS+=" -O0 --coverage"
else
	echo "usage: ./build.sh [b|d] [path to cpp file]"
	exit 1
fi

SRC=$ROOT/$2
EXE=$ROOT/../build/tests/$2.e

mkdir -p `dirname $EXE`
g++ $FLAGS -o $EXE $SRC
