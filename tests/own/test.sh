#!/bin/bash
set -e
cd ..
ROOT=`pwd`

if [ $# -lt 2 ]; then
    echo "usage: ./test.sh [b|d] [path to cpp file] [deterministic|fuzz|bench]"
    exit 1
fi

./build.sh $1 own/$2
echo start
time $ROOT/../build/tests/own/$2.e ${@:3}
