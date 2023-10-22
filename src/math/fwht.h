#pragma once
#include "../template.h"

// Fast Walsh-Hadamard Transform; O(n lg n)
// Input must be power of 2!
// Uncommented version is for XOR.
// OR version is equivalent to sum-over-subsets
// (Zeta transform, inverse is Moebius).
// AND version is same as sum-over-supersets.
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastSubsetTransform.h
template<bool inv>
void fwht(auto& b) {
	for (int s = 1; s < sz(b); s *= 2) {
		for (int i = 0; i < sz(b); i += s*2) {
			rep(j, i, i+s) {
				auto &x = b[j], &y = b[j+s];
				tie(x, y) = make_pair(x+y, x-y); // XOR
				// x += inv ? -y : y;            // AND
				// y += inv ? -x : x;            // OR
			}
		}
	}

	// ONLY FOR XOR:
	if (inv) each(e, b) e /= sz(b);
}

// Compute convolution of a and b such that
// ans[i#j] += a[i]*b[j], where # is OR, AND
// or XOR, depending on FWHT version.
// Stores result in a; time: O(n lg n)
// Both arrays must be of same size = 2^n!
void bitConv(auto& a, auto b) {
	fwht<0>(a);
	fwht<0>(b);
	rep(i, 0, sz(a)) a[i] *= b[i];
	fwht<1>(a);
}
