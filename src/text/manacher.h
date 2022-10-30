#pragma once
#include "../template.h"

// Manacher algorithm; time: O(n)
// Finds largest radiuses for palindromes:
// r[2*i] = for center at i (single letter = 1)
// r[2*i+1] = for center between i and i+1
template<class T> vi manacher(const T& str) {
	int n = sz(str)*2, c = 0, e = 1;
	vi r(n, 1);
	auto get = [&](int i) { return i%2 ? 0 :
		(i >= 0 && i < n ? str[i/2] : i); };

	rep(i, 0, n) {
		if (i < e) r[i] = min(r[c*2-i], e-i);
		while (get(i-r[i]) == get(i+r[i])) r[i]++;
		if (i+r[i] > e) c = i, e = i+r[i]-1;
	}

	rep(i, 0, n) r[i] /= 2;
	return r;
}
