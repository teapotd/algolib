export FL="-std=c++11 -O2 -g -pedantic -Wall -Wextra -Wfatal-errors -Wshadow
           -Wconversion -Wfloat-equal -Wlogical-op -Wformat=2"

export DFL="-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
            -fsanitize=address,undefined"

b()   ( g++ $FL      -o $1.e $1.cpp )  # Build:            b PROGRAM
d()   ( g++ $FL $DFL -o $1.e $1.cpp )  # Build with debug: d PROGRAM
run() ( $1 $2 && time ./$2.e        )  # Run:              run b|d PROGRAM

loo() (                                # Run in loop:      tim b|d PROGRAM GENERATOR
	set -e; $1 $2; $1 $3
	for ((;;)) { ./$3.e > gen.in; time ./$1.e < gen.in > p1.out; }
)

cmp() (                                # Compare outputs:  cmp b|d PROGRAM1 PROGRAM2 GENERATOR
	set -e; $1 $2; $1 $3; $1 $4

	for ((;;)) {
		./$4.e > gen.in;          echo -n 0
		./$2.e < gen.in > p1.out; echo -n 1
		./$3.e < gen.in > p2.out; echo -n 2
		diff p1.out p2.out;       echo -n Y
	}
)
