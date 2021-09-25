build()(
	g++ $@ -o $1.e -DLOC -std=c++11           \
	    -Wall -Wextra -Wfatal-errors -Wshadow \
	    -Wlogical-op -Wconversion -Wfloat-equal
)

b()( build $@ -O2 )

d()( build $@ -fsanitize=address,undefined \
              -D_GLIBCXX_DEBUG -g )

run()( $1 $2 && echo start >&2 && time ./$2.e )

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
		diff p1.out p2.out;       echo -n Y
	}
)

# Other flags:
# -Wformat=2 -Wshift-overflow=2 -Wcast-qual
# -Wcast-align -Wduplicated-cond
# -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
# -fno-sanitize-recover -fstack-protector

# Stacktrace on STL assert:
#   g++ -D_GLIBCXX_DEBUG -H test.cpp 2>&1
#     >/dev/null | grep "debug/macros.h"
#   #ifdef __SANITIZE_ADDRESS__
#   extern "C"
#     void __sanitizer_print_stack_trace();
