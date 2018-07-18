#pragma once
#include "../template.h"

using ull = uint64_t;

#define T64(s,up,down)               \
	for (ull i=0; i<64; i+=s*2)        \
		for (ull j = i; j < i+s; j++) {  \
			ull a = (M[j] >> s) & up;      \
			ull b = (M[j+s] << s) & down;  \
			M[j] = (M[j] & up) | b;        \
			M[j+s] = (M[j+s] & down) | a;  \
		}

void transpose64(array<ull, 64>& M) {
	T64(1,0x5555555555555555,0xAAAAAAAAAAAAAAAA);
	T64(2,0x3333333333333333,0xCCCCCCCCCCCCCCCC);
	T64(4,0xF0F0F0F0F0F0F0F,0xF0F0F0F0F0F0F0F0);
	T64(8,0xFF00FF00FF00FF,0xFF00FF00FF00FF00);
	T64(16,0xFFFF0000FFFF,0xFFFF0000FFFF0000);
	T64(32,0xFFFFFFFF,0xFFFFFFFF00000000);
}
