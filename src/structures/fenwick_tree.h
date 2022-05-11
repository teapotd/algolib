#pragma once
#include "../template.h"

// Fenwick tree (BIT tree); space: O(n)
// Default version: prefix sums
struct Fenwick {
	using T = int;
	static constexpr T ID = 0;
	T f(T a, T b) { return a+b; }

	vector<T> s;
	Fenwick(int n = 0) : s(n, ID) {}

	// A[i] = f(A[i], v); time: O(lg n)
	void modify(int i, T v) {
		for (; i < sz(s); i |= i+1) s[i]=f(s[i],v);
	}

	// Get f(A[0], ..., A[i-1]); time: O(lg n)
	T query(int i) {
		T v = ID;
		for (; i > 0; i &= i-1) v = f(v, s[i-1]);
		return v;
	}

	// Find smallest i such that
	// f(A[0],...,A[i-1]) >= val; time: O(lg n)
	// Prefixes must have non-descreasing values.
	int lowerBound(T val) {
		if (val <= ID) return 0;
		int i = -1, mask = 1;
		while (mask <= sz(s)) mask *= 2;
		T off = ID;

		while (mask /= 2) {
			int k = mask+i;
			if (k < sz(s)) {
				T x = f(off, s[k]);
				if (val > x) i=k, off=x;
			}
		}
		return i+2;
	}
};
