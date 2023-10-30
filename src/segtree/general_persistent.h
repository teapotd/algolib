#pragma once
#include "../template.h"

// Highly configurable interval-interval
// persistent segment tree; space: O(q lg n)
// First tree version number is 0.
struct SegTree {
	// Choose/write configuration
	#include "general_config.h"

	vector<Agg> agg{{}}; // Aggregated data
	vector<T> lazy{ID};  // Lazy tags
	vector<bool> cow{0}; // Copy children on push
	vi L{0}, R{0};       // Children links
	int len{1};          // Number of leaves

	// Initialize tree for n elements; O(lg n)
	SegTree(int n = 0) {
		int k = 3;
		while (len < n) len *= 2, k += 3;
		rep(i, 1, k) fork(0);
		iota(all(R)-3, 3);
		L = R;
		if (n--) {
			agg[k -= 3].leaf();
			agg[k+1].leaf();
			for (int i = k-3; i >= 0; i -= 3, n /= 2)
				(n%2 ? L[i] : ++R[i])++;
			while (k--) pull(k);
		}
	}

	// New version from version `i`; time: O(1)
	int fork(int i) {
		L.pb(L[i]); R.pb(R[i]); cow.pb(cow[i] = 1);
		agg.pb(agg[i]); lazy.pb(lazy[i]);
		return sz(L)-1;
	}

	void pull(int i) {
		(agg[i] = agg[L[i]]).merge(agg[R[i]]);
	}

	void push(int i, bool w) {
		if (w || lazy[i] != ID) {
			if (cow[i]) {
				int x = fork(L[i]), y = fork(R[i]);
				L[i] = x; R[i] = y; cow[i] = 0;
			}
			agg[L[i]].apply(lazy[L[i]], lazy[i]);
			agg[R[i]].apply(lazy[R[i]], lazy[i]);
			lazy[i] = ID;
		}
	}

	template<bool U>
	void go(int vb, int ve, int i, int b, int e,
	        auto fn) {
		if (vb < e && b < ve)
			if (b < vb || ve < e || !fn(i)) {
				int m = (b+e) / 2;
				push(i, U);
				go<U>(vb, ve, L[i], b, m, fn);
				go<U>(vb, ve, R[i], m, e, fn);
				if (U) pull(i);
			}
	}

	// Modify interval [b;e) with val
	// in tree version `j`; time: O(lg n)
	void update(int j, int b, int e, T val) {
		go<1>(b, e, j, 0, len, [&](int i) {
			return agg[i].apply(lazy[i], val);
		});
	}

	// Query interval [b;e) in tree version `j`;
	Agg query(int j, int b, int e) { // O(lg n)
		Agg t;
		go<0>(b, e, j, 0, len, [&](int i) {
			return t.merge(agg[i]), 1;
		});
		return t;
	}

	// Find smallest `j` such that
	// g(aggregate of [0,j)) is true
	// in tree version `i`; time: O(lg n)
	// The function `g` must be monotonic.
	// Returns -1 if no such prefix exists.
	int lowerBound(int i, auto g) {
		if (!g(agg[i])) return -1;
		Agg x, s;
		int p = 0, k = len;
		while (L[i]) {
			push(i, 0);
			(s = x).merge(agg[L[i]]);
			k /= 2;
			i = g(s) ? L[i] : (x = s, p += k, R[i]);
		}
		return p + !g(x);
	}
};
