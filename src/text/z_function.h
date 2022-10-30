#pragma once
#include "../template.h"

// Computes Z function array; time: O(n)
// zf[i] = max common prefix of str and str[i:]
template<class T> vi prefPref(const T& str) {
	int n = sz(str), b = 0, e = 1;
	vi zf(n);
	rep(i, 1, n) {
		if (i < e) zf[i] = min(zf[i-b], e-i);
		while (i+zf[i] < n &&
			str[zf[i]] == str[i+zf[i]]) zf[i]++;
		if (i+zf[i] > e) b = i, e = i+zf[i];
	}
	zf[0] = n;
	return zf;
}
