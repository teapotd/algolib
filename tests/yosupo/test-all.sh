#!/bin/bash
set -e

if [ $# -ne 1 ]; then
    echo "usage: ./test-all.sh [b|d]"
    exit 1
fi

for CPP_FILE in */*.cpp; do
	echo
	echo ================================
	echo $CPP_FILE
	echo ================================
	./test.sh $1 $CPP_FILE
done
