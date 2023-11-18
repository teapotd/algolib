#!/bin/bash
set -e -o pipefail

if [ $# -lt 2 ]; then
    echo "usage: ./test.sh [b|d|c] [files...]"
    exit 1
fi

BUILD_MODE=$1
FILES=$(find ${@:2} -name '*.cpp' | sort)

cd ..
ROOT=`pwd`

if [ $BUILD_MODE = "c" ]; then
	./clear-coverage.sh
fi

for CPP_FILE in $FILES; do
	echo
	echo ================================================================
	echo $CPP_FILE
	echo ================================================================

	./build.sh $BUILD_MODE yosupo/$CPP_FILE

	EXE=$ROOT/../build/tests/yosupo/$CPP_FILE.e
	PROBLEM_DIR=$ROOT/library-checker-problems/${CPP_FILE%%.*}
	IN_DIR=$PROBLEM_DIR/in
	OUT_DIR=$PROBLEM_DIR/out
	CHECKER=$PROBLEM_DIR/checker
	GOT_FILE=$ROOT/../build/got.out

	$ROOT/library-checker-problems/generate.py $PROBLEM_DIR/info.toml

	for IN_FILE in $IN_DIR/*.in; do
		TEST_NAME=`basename ${IN_FILE%.*}`
		OUT_FILE=$OUT_DIR/$TEST_NAME.out
		echo
		echo --------------------------------
		echo $TEST_NAME
		rm -f $GOT_FILE
		time $EXE < $IN_FILE > $GOT_FILE
		if [[ $(< $GOT_FILE) != "IGNORE-TEST" ]]; then
			$CHECKER $IN_FILE $GOT_FILE $OUT_FILE
		else
			echo "warning: ignoring test"
		fi
	done
done

if [ $BUILD_MODE = "c" ]; then
	./report-coverage.sh
fi
