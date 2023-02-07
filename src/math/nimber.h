#pragma once
#include "../template.h"

// Arithmetic over 64-bit nimber field.
// Operations on nimbers are defined as:
// a+b = mex({a'+b : a' < a} u {a+b' : b' < b})
// ab  = mex({a'b+ab'+a'b' : a' < a, b' < b})
// Nimbers smaller than 2^2^k
// form a field of characteristic 2.
// Addition is equivalent to bitwise xor.
//! Source: https://judge.yosupo.jp/submission/92308

using ull = uint64_t;

uint16_t npw[1<<16], nlg[1<<16];

// Multiply 64-bit nimbers a and b.
template<int half = 32, bool prec = 0>
ull nimMul(ull a, ull b) {
	if (a < 2 || b < 2) return a * b;
	if (!prec && half <= 8)
		return npw[(nlg[a] + nlg[b]) % 0xFFFF];

	constexpr ull tot = 1ull << half;
	ull c = a % tot, d = a >> half;
	ull e = b % tot, f = b >> half;

	ull p = nimMul<half/2, prec>(c, e);
	ull r = nimMul<half/2, prec>(d, f);
	ull s = nimMul<half/2, prec>(c^d, e^f);
	ull t = nimMul<half/2, prec>(r, tot/2);
	return p ^ t ^ (p ^ s) << half;
}

int dummy = ([]() {
	rep(i, npw[0] = 1, 0xFFFF) {
		ull v = nimMul<16, 1>(npw[i-1], -1);
		nlg[npw[i] = uint16_t(v)] = uint16_t(i);
	}
}(), 0);

// Compute a^e under nim arithmetic;
// O(lg M) nimber multiplications
ull nimPow(ull a, ull e) {
	ull t = 1;
	while (e) {
		if (e % 2) t = nimMul(t, a);
		e /= 2; a = nimMul(a, a);
	}
	return t;
}

// Compute inverse of a in 2^64 nim-field;
// O(lg M) nimber multiplications
ull nimInv(ull a) {
	return nimPow(a, -2);
}
