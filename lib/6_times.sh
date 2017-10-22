#!/bin/bash
set -e
./build.sh $1; ./build.sh $2

while :; do
	$2.e > gen.in
	time $1.e < gen.in > p1.out
done
