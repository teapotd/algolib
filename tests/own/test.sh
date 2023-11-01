#!/bin/bash
set -e -o pipefail

if [ $# -lt 3 ]; then
    echo "usage: ./test.sh [b|d] [deterministic|fuzz|bench] [files...]"
    exit 1
fi

BUILD_MODE=$1
TEST_MODE=$2
FILES=$(find ${@:3} -name '*.cpp' | sort)

cd ..
ROOT=`pwd`

for CPP_FILE in $FILES; do
    echo
    echo ================================================================
    echo $CPP_FILE
    echo ================================================================
    ./build.sh $BUILD_MODE own/$CPP_FILE
    echo start
    time $ROOT/../build/tests/own/$CPP_FILE.e $TEST_MODE
done
