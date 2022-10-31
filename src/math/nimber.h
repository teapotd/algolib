#pragma once
#include "../template.h"

// Nimbers are defined as sizes of Nim heaps.
// Operations on nimbers are defined as:
// a+b = mex({a'+b : a' < a} u {a+b' : b' < b})
// ab  = mex({a'b+ab'+a'b' : a' < a, b' < b})
// Nimbers smaller than M = 2^2^k form a field.
// Addition is equivalent to xor, meanwhile
// multiplication can be evaluated
// in O(lg^2 M) after precomputing.

using ull = uint64_t;
ull nbuf[64][64]; // Nim-products for 2^i * 2^j

// Multiply nimbers; time: O(lg^2 M)
// WARNING: Call initNimMul() before using.
ull nimMul(ull a, ull b) {
	ull ret = 0;
	for (ull s = a; s; s &= (s-1))
		for (ull t = b; t; t &= (t-1))
			ret ^= nbuf[__builtin_ctzll(s)]
			           [__builtin_ctzll(t)];
	return ret;
}

// Initialize nim-products lookup table
void initNimMul() {
	rep(i, 0, 64)
		nbuf[i][0] = nbuf[0][i] = 1ull << i;
	rep(b, 1, 64) rep(a, 1, b+1) {
		int i = 1 << __lg(a), j = 1 << __lg(b);
		ull t = nbuf[a-i][b-j];
		if (i < j)
			t = nimMul(t, 1ull << i) << j;
		else
			t = nimMul(t, 1ull << (i-1)) ^ (t << i);
		nbuf[a][b] = nbuf[b][a] = t;
	}
}

// Compute a^e under nim arithmetic; O(lg^3 M)
// WARNING: Call initNimMul() before using.
ull nimPow(ull a, ull e) {
	ull t = 1;
	while (e) {
		if (e % 2) t = nimMul(t, a);
		e /= 2; a = nimMul(a, a);
	}
	return t;
}

// Compute inverse of a in 2^64 nim-field;
// time: O(lg^3 M)
// WARNING: Call initNimMul() before using.
ull nimInv(ull a) {
	return nimPow(a, ull(-2));
}

// If you need to multiply many nimbers by
// the same value you can use this to speedup.
// WARNING: Call initNimMul() before using.
struct NimMult {
	ull M[64] = {0};

	// Initialize lookup; time: O(lg^2 M)
	NimMult(ull a) {
		for (ull t=a; t; t &= (t-1)) rep(i, 0, 64)
			M[i] ^= nbuf[__builtin_ctzll(t)][i];
	}

	// Multiply by b; time: O(lg M)
	ull operator()(ull b) {
		ull ret = 0;
		for (ull t = b; t; t &= (t-1))
			ret ^= M[__builtin_ctzll(t)];
		return ret;
	}
};
