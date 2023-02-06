#pragma once
#include "../template.h"

// __builtin_popcount - count number of 1 bits
// __builtin_clz - count most significant 0s
// __builtin_ctz - count least significant 0s
// __builtin_ffs - like ctz, but indexed from 1
//                 returns 0 for 0
// For ll version add ll to name

using ull = uint64_t;

// Transpose 64x64 bit matrix
void transpose64(array<ull, 64>& M) {
	#define T(s,up)                        \
		for (ull i=0; i<64; i+=s*2)          \
			for (ull j = i; j < i+s; j++) {    \
				ull a = (M[j] >> s) & up;        \
				ull b = (M[j+s] & up) << s;      \
				M[j] = (M[j] & up) | b;          \
				M[j+s] = (M[j+s] & (up<<s)) | a; \
			}
	T(1,  0x5555'5555'5555'5555);
	T(2,  0x3333'3333'3333'3333);
	T(4,   0xF0F'0F0F'0F0F'0F0F);
	T(8,    0xFF'00FF'00FF'00FF);
	T(16,      0xFFFF'0000'FFFF);
	T(32,           0xFFFF'FFFFLL);
	#undef T
}

// Lexicographically next mask with same
// amount of ones.
int nextSubset(int v) {
	int t = v | (v - 1);
	return (t + 1) | (((~t & -~t) - 1) >>
			(__builtin_ctz(v) + 1));  
}
