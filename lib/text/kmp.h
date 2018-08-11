#pragma once
#include "../template.h"

// KMP algorithm; helper function
// Use functions below.
template<class T>
void kmp(const T& cur, const T& prev, Vi& ps) {
	each(x, cur) {
		int k = ps.back();
		while (k >= 0 && prev[k] != x) k = ps[k];
		ps.pb(k+1);
	}
}

// Computes prefsuf array; time: O(n)
// ps[i] = max prefsuf of [0;i); ps[0] := -1
template<class T> Vi prefSuf(const T& str) {
	Vi ps; ps.pb(-1);
	kmp(str, str, ps);
	return ps;
}

// Finds occurences of pat in vec; time: O(n)
// Returns starting indices of matches.
// `neutral` is separator to be used for concat
template<class T>
Vi match(const T& str, const T& pat) {
	Vi ret, ps; ps.pb(-1);
	kmp(pat, pat, ps);
	kmp(str, pat, ps);
	rep(i, sz(ps)-sz(str), sz(ps)) {
		if (ps[i]==sz(pat)) ret.pb(i-2*sz(pat)-1);
	}
	return ret;
}
