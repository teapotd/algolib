export FL="-O2 -DLOC -g -std=c++11 -Wall -Wextra -Wfatal-errors -Wshadow
           -Wconversion -Wfloat-equal -Wlogical-op"

export DFL="-D_GLIBCXX_DEBUG -fsanitize=address,undefined -fvisibility=hidden"

b()   ( g++ $FL      -o $1.e $1.cpp )  # Build:            b PROGRAM
d()   ( g++ $FL $DFL -o $1.e $1.cpp )  # Build with debug: d PROGRAM
run() ( $1 $2 && time ./$2.e        )  # Run:              run b|d PROGRAM

loo() (                                # Run in loop:      tim b|d PROGRAM GENERATOR
	set -e; $1 $2; $1 $3
	for ((;;)) { ./$3.e > gen.in; time ./$2.e < gen.in > p1.out; }
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

# Other flags:
# -Wformat=2 -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align
# -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fno-sanitize-recover -fstack-protector
