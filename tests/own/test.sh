#!/bin/bash
set -e -o pipefail

if [ $# -lt 3 ]; then
    echo "usage: ./test.sh [b|d|c] [deterministic|fuzz|bench] [files...]"
    exit 1
fi

BUILD_MODE=$1
TEST_MODE=$2
FILES=$(find ${@:3} -name '*.cpp' | sort)

cd ..

if [ $BUILD_MODE = "c" ]; then
	./clear-coverage.sh
fi

for CPP_FILE in $FILES; do
    echo
    echo ================================================================
    echo $CPP_FILE
    echo ================================================================
    ./build.sh $BUILD_MODE own/$CPP_FILE
    echo start
    time ../build/tests/own/$CPP_FILE.e $TEST_MODE
done

if [ $BUILD_MODE = "c" ]; then
	./report-coverage.sh
fi
