#pragma once
#include "../template.h"

// Fenwick tree (BIT tree); space: O(n)
// Default version: prefix sums
struct Fenwick {
	using T = int;
	static constexpr T ID = 0;
	T f(T a, T b) { return a+b; }

	vector<T> s;
	Fenwick(int n = 0) { init(n); }
	void init(int n)   { s.assign(n, 0); }

	// A[i] = f(A[i], v); time: O(lg n)
	void modify(int i, T v) {
		for (; i < sz(s); i |= i+1) s[i]=f(s[i],v);
	}

	// Get f(A[0], .., A[i-1]); time: O(lg n)
	T query(int i) {
		T v = 0;
		for (; i > 0; i &= i-1) v = f(v, s[i-1]);
		return v;
	}
};
