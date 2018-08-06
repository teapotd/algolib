#pragma once
#include "../template.h"

// Fenwick tree (BIT tree); space: O(n)
template<class T> struct Fenwick {
	vector<T> s;
	Fenwick(int n = 0) { init(0); }
	void init(int n)   { s.assign(n, 0); }

	// Add v to i-th element; time: O(lg n)
	void modify(int i, T v) {
		for (; i < sz(s); i |= i+1) s[i] += v;
	}

	// Get prefix sum [0;i); time: O(lg n)
	T query(int i) {
		T v = 0;
		for (; i > 0; i &= i-1) v += s[i-1];
		return v;
	}
};
