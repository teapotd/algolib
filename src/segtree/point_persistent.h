#pragma once
#include "../template.h"

// Point-interval persistent segment tree
// - T - stored data type
// - ID - neutral element for query operation
// - f(a, b) - associative aggregate function
// First tree version number is 0.
struct SegTree {
	#ifndef SEGTREE_CONFIG_OVERRIDE //!HIDE
	using T = int;
	static constexpr T ID = INT_MIN;
	T f(T a, T b) { return max(a, b); }
	#endif //!HIDE

	vector<T> agg;    // Aggregated data
	vector<bool> cow; // Copy children on write?
	vi L, R;          // Children links
	int len{1};       // Number of leaves

	// Initialize tree for n elements; O(lg n)
	SegTree(int n = 0, T def = 0) {
		int k = 3;
		while (len < n) len *= 2, k += 3;

		agg.resize(k, ID);
		cow.resize(k, 1);
		L.resize(k);
		R.resize(k);
		if (!n--) return;

		k -= 3;
		agg[k] = agg[k+1] = def;
		rep(i, 0, k) L[i] = R[i] = i+3;

		for (int i = k-3; i >= 0; i -= 3, n /= 2) {
			if (n % 2) L[i] = i+4;
			else R[i] = i+5;
		}

		while (k--)
			agg[k] = f(agg[L[k]], agg[R[k]]);
	}

	// New version from version `i`; time: O(1)
	int fork(int i) {
		L.pb(L[i]); R.pb(R[i]);
		agg.pb(agg[i]); cow.pb(cow[i] = 1);
		return sz(L)-1;
	}

	// Set element `pos` to `val` in version `i`;
	// time: O(lg n)
	void set(int i, int pos, T val,
           int b = 0, int e = -1) {
		if (L[i]) {
			if (e < 0) e = len;
			int m = (b+e) / 2;
			if (cow[i]) {
				int x = fork(L[i]), y = fork(R[i]);
				L[i] = x; R[i] = y; cow[i] = 0;
			}
			if (pos < m) set(L[i], pos, val, b, m);
			else set(R[i], pos, val, m, e);
			agg[i] = f(agg[L[i]], agg[R[i]]);
		} else {
			agg[i] = val;
		}
	}

	// Query interval [b;e) in tree version `i`;
	// time: O(lg n)
	T query(int i, int vb, int ve,
	        int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (vb >= e || b >= ve) return ID;
		if (b >= vb && e <= ve) return agg[i];
		int m = (b+e) / 2;
		return f(query(L[i], vb, ve, b, m),
		         query(R[i], vb, ve, m, e));
	}

	// Find smallest `j` such that
	// g(aggregate of [0,j)) is true
	// in tree version `i`; time: O(lg n)
	// The function `g` must be monotonic.
	// Returns -1 if no such prefix exists.
	int lowerBound(int i, auto g) {
		if (!g(agg[i])) return -1;
		T x = ID;
		int p = 0, k = len;
		while (L[i]) {
			T s = f(x, agg[L[i]]);
			k /= 2;
			i = g(s) ? L[i] : (x = s, p += k, R[i]);
		}
		return p + !g(x);
	}
};
