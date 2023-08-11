#!/bin/bash
set -e

if [ $# -lt 1 ]; then
    echo "usage: ./test-all.sh [b|d] [deterministic|bench]"
    exit 1
fi

for CPP_FILE in */*.cpp; do
	echo
	echo ================================
	echo $CPP_FILE
	echo ================================
	./test.sh $1 $CPP_FILE $2
done
