#pragma once
#include "../template.h"

// Computes prefsuf array; time: O(n)
// ps[i] = max prefsuf of [0;i); ps[0] := -1
template<class T> Vi kmp(const T& str) {
	Vi ps; ps.pb(-1);
	each(x, str) {
		int k = ps.back();
		while (k >= 0 && str[k] != x) k = ps[k];
		ps.pb(k+1);
	}
	return ps;
}

// Finds occurences of pat in vec; time: O(n)
// Returns starting indices of matches.
template<class T>
Vi match(const T& str, T pat) {
	int n = sz(pat);
	pat.pb(-1); // SET TO SOME UNUSED CHARACTER
	pat.insert(pat.end(), all(str));
	Vi ret, ps = kmp(pat);
	rep(i, 0, sz(ps)) {
		if (ps[i] == n) ret.pb(i-2*sz(pat)-2);
	}
	return ret;
}
