#pragma once
#include "../template.h"

// __builtin_popcount - count number of 1 bits
// __builtin_clz - count most significant 0s
// __builtin_ctz - count least significant 0s
// __builtin_ffs - like ctz, but indexed from 1
// For ll version add ll to name

using ull = uint64_t;

#define T64(s,up)                      \
	for (ull i=0; i<64; i+=s*2)          \
		for (ull j = i; j < i+s; j++) {    \
			ull a = (M[j] >> s) & up;        \
			ull b = (M[j+s] & up) << s;      \
			M[j] = (M[j] & up) | b;          \
			M[j+s] = (M[j+s] & (up<<s)) | a; \
		}

// Transpose 64x64 bit matrix
void transpose64(array<ull, 64>& M) {
	T64(1,  0x5555555555555555);
	T64(2,  0x3333333333333333);
	T64(4,  0xF0F0F0F0F0F0F0F);
	T64(8,  0xFF00FF00FF00FF);
	T64(16, 0xFFFF0000FFFF);
	T64(32, 0xFFFFFFFFLL);
}
