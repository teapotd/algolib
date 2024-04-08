#!!CONVERT-BREAKS
b()( g++ -DLOC -O2 -std=c++20 -Wall -W \
		-Wfatal-errors -Wconversion -Wshadow \
		-Wlogical-op -Wfloat-equal -o $1.e $@ )

d()( b $@ -O0 -g -D_GLIBCXX_DEBUG \
		-fsanitize=address,undefined )

run()( $@ && echo start >&2 && time ./$2.e )
