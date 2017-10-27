# UNTESTED
#!/bin/bash
set -e
./dbuild.sh $1; ./build.sh $2; ./build.sh $3

while :; do
	$3.e > gen.in;          echo -n 0
	$1.e < gen.in > p1.out; echo -n 1
	$2.e < gen.in > p2.out; echo -n 2
	diff p1.out p2.out;     echo -n Y
done
