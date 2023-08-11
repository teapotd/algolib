#pragma once
#include "../template.h"

// Manacher algorithm; time: O(n)
// Finds largest radiuses for palindromes:
// p[0][i] for center between i-1 and i
// p[1][i] for center at i (single letter = 0)
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Manacher.h
template<class T>
array<vi, 2> manacher(const T& s) {
	int n = sz(s), l = 0, r = 0;
	array<vi, 2> p = {vi(n+1), vi(n)};
	rep(i, 0, n) rep(z, 0, 2) {
		int t = r-i+!z, &x = p[z][i];
		if (i < r) x = min(t, p[z][l+t]);
		int b = i-x-1, e = i+x+z;
		while (b >= 0 && e < n && s[b] == s[e])
			x++, b--, e++;
		if (r < e) l = b+1, r = e-1;
	}
	return p;
}
