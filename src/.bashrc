b()( g++ -DLOC -O2 -std=c++20                 \
         -Wall -W -Wfatal-errors -Wconversion \
         -Wshadow -Wlogical-op -Wfloat-equal  \
         -o $1.e $@ )

d()( b $@ -O0 -g -D_GLIBCXX_DEBUG \
          -fsanitize=address,undefined )

run()( $@ && echo start >&2 && time ./$2.e )

loo()(
	set -e; $1 $2; $1 $3
	for ((;;)) {
		./$3.e > gen.in
		time ./$2.e < gen.in > gen.out
	}
)

cmp()(
	set -e; $1 $2; $1 $3; $1 $4
	for ((;;)) {
		./$4.e > gen.in;          echo -n 0
		./$2.e < gen.in > p1.out; echo -n 1
		./$3.e < gen.in > p2.out; echo -n 2
		diff p1.out p2.out
	}
)

# Other compilation flags:
# -Wformat=2 -Wshift-overflow=2 -Wcast-qual
# -Wcast-align -Wduplicated-cond
# -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
# -fno-sanitize-recover -fstack-protector
# -fopt-info-all -fopt-info-missed
