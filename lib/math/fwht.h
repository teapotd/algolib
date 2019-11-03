#pragma once
#include "../template.h"

// Fast Walsh-Hadamard Transform; O(n lg n)
// Input must be power of 2!
// Uncommented version is for XOR.
// UNTESTED
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/FastSubsetTransform.h
template<class T, bool inv>
void fwht(vector<T>& b) {
	for (int s = 1; s < sz(b); s *= 2) {
		for (int i = 0; i < sz(b); i += s*2) {
			rep(j, i, i+s) {
				auto &x = b[j], &y = b[j+s];
				tie(x, y) =
				   mp(x+y, x-y);                  //XOR
				// inv ? mp(y-x, x) : mp(y, x+y); //AND
				// inv ? mp(y, x-y) : mp(x+y, y); //OR
			}
		}
	}

	// ONLY FOR XOR:
	if (inv) each(e, b) e /= sz(b);
}

// BIT-convolve a and b, store result in a;
// time: O(n lg n)
// Both arrays must be of same size = 2^n!
template<class T>
void convolve(vector<T>& a, vector<T> b) {
	fwht<T, 0>(a);
	fwht<T, 0>(b);
	rep(i, 0, sz(a)) a[i] *= b[i];
	fwht<T, 1>(a);
}
