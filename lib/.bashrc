b()(
	g++ $@ -o $1.e -DLOC -O2 -g -std=c++11 \
	    -Wall -Wextra -Wfatal-errors -Wshadow \
	    -Wlogical-op -Wconversion -Wfloat-equal
)

d()( b $@ -fsanitize=address,undefined \
	        -D_GLIBCXX_DEBUG )

# cmp()(
# 	set -e; $1 $2; $1 $3; $1 $4
# 	for ((;;)) {
# 		./$4.e > gen.in;          echo -n 0
# 		./$2.e < gen.in > p1.out; echo -n 1
# 		./$3.e < gen.in > p2.out; echo -n 2
# 		diff p1.out p2.out;       echo -n Y
# 	}
# )

# Other flags:
# -Wformat=2 -Wshift-overflow=2 -Wcast-qual
# -Wcast-align -Wduplicated-cond
# -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
# -fno-sanitize-recover -fstack-protector
