#!/bin/bash
set -e
cd ..
ROOT=`pwd`

if [ $# -lt 2 ]; then
    echo "usage: ./test.sh [b|d] [path to cpp file] [arguments...]"
    exit 1
fi

./build.sh $1 manual/$2
echo start
time $ROOT/../build/tests/manual/$2.e ${@:3}
