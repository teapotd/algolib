#!/bin/bash
set -e
cd ..
ROOT=`pwd`

if [ $# -ne 2 ]; then
    echo "usage: ./test.sh [b|d] [path to cpp file]"
    exit 1
fi

./build.sh $1 yosupo/$2

EXE=$ROOT/../build/tests/yosupo/$2.e
PROBLEM_DIR=$ROOT/library-checker-problems/${2%.*}
IN_DIR=$PROBLEM_DIR/in
OUT_DIR=$PROBLEM_DIR/out
CHECKER=$PROBLEM_DIR/checker
GOT_FILE=$ROOT/../build/got.out

for IN_FILE in $IN_DIR/*.in; do
	TEST_NAME=`basename ${IN_FILE%.*}`
	OUT_FILE=$OUT_DIR/$TEST_NAME.out
	echo
	echo ----------------
	echo $TEST_NAME
	rm -f $GOT_FILE
	time $EXE < $IN_FILE > $GOT_FILE
	$CHECKER $IN_FILE $GOT_FILE $OUT_FILE
done
