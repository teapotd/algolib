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
			while (k--)
				(agg[k] = agg[L[k]]).merge(agg[R[k]]);
		}
	}

	// New version from version `i`; time: O(1)
	int fork(int i) {
		L.pb(L[i]); R.pb(R[i]); cow.pb(cow[i] = 1);
		agg.pb(agg[i]); lazy.pb(lazy[i]);
		return sz(L)-1;
	}

	void push(int i, int s, bool w) {
		if (w || lazy[i] != ID) {
			if (cow[i]) {
				int x = fork(L[i]), y = fork(R[i]);
				L[i] = x; R[i] = y; cow[i] = 0;
			}
			agg[L[i]].apply(lazy[L[i]],lazy[i],s/2);
			agg[R[i]].apply(lazy[R[i]],lazy[i],s/2);
			lazy[i] = ID;
		}
	}

	// Modify interval [vb;ve) with val
	// in tree version `i`; time: O(lg n)
	// [vb;ve) is assumed to be within [0;n).
	T update(int i, int vb, int ve, T val,
	         int b = 0, int e = 0) {
		if (!e) e = len;
		if (vb >= e || b >= ve) return val;

		if (b >= vb && e <= ve &&
		    agg[i].apply(lazy[i], val, e-b))
			return val;

		int m = (b+e) / 2;
		push(i, e-b, 1);
		val = update(L[i], vb, ve, val, b, m);
		val = update(R[i], vb, ve, val, m, e);
		(agg[i] = agg[L[i]]).merge(agg[R[i]]);
		return val;
	}

	// Query interval [vb;ve)
	// in tree version `i`; time: O(lg n)
	Agg query(int i, int vb, int ve,
	          int b = 0, int e = 0) {
		if (!e) e = len;
		if (vb >= e || b >= ve) return {};
		if (b >= vb && e <= ve) return agg[i];

		int m = (b+e) / 2;
		push(i, e-b, 0);
		Agg t = query(L[i], vb, ve, b, m);
		t.merge(query(R[i], vb, ve, m, e));
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
			push(i, k, 0);
			(s = x).merge(agg[L[i]]);
			k /= 2;
			i = g(s) ? L[i] : (x = s, p += k, R[i]);
		}
		return p + !g(x);
	}
};
