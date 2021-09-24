#pragma once
#include "../template.h"

// Highly configurable (interval; interval)
// persistent segment tree;
// space: O(queries lg n)
// First tree version number is 0.
struct SegTree {
	// Choose/write configuration
	#include "segtree_config.h"

	vector<Agg> agg; // Aggregated data for nodes
	vector<T> lazy;  // Lazy tags for nodes
	vector<bool> cow; // Copy children on push?
	Vi L, R;         // Children links
	int len{1};      // Number of leaves

	// Initialize tree for n elements; O(lg n)
	SegTree(int n = 0) {
		int k = 1;
		while (len < n) len *= 2, k++;

		agg.resize(k);
		lazy.resize(k, ID);
		cow.resize(k, 1);
		L.resize(k);
		R.resize(k);
		agg[--k].leaf();

		while (k--) {
			(agg[k] = agg[k+1]).merge(agg[k+1]);
			L[k] = R[k] = k+1;
		}
	}

	// New version from version `i`; time: O(1)
	// First version number is 0.
	int fork(int i) {
		L.pb(L[i]); R.pb(R[i]); cow.pb(cow[i] = 1);
		agg.pb(agg[i]); lazy.pb(lazy[i]);
		return sz(L)-1;
	}

	void push(int i, int s, bool w) {
		bool has = (lazy[i] != ID);
		if ((has || w) && cow[i]) {
			int a = fork(L[i]), b = fork(R[i]);
			L[i] = a; R[i] = b; cow[i] = 0;
		}
		if (has) {
			agg[L[i]].apply(lazy[L[i]],lazy[i],s/2);
			agg[R[i]].apply(lazy[R[i]],lazy[i],s/2);
			lazy[i] = ID;
		}
	}

	// Modify interval [vb;ve) with val
	// in tree version `i`; time: O(lg n)
	T update(int i, int vb, int ve, T val,
	         int b = 0, int e = -1) {
		if (e < 0) e = len;
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
	          int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (vb >= e || b >= ve) return {};
		if (b >= vb && e <= ve) return agg[i];

		int m = (b+e) / 2;
		push(i, e-b, 0);
		Agg t = query(L[i], vb, ve, b, m);
		t.merge(query(R[i], vb, ve, m, e));
		return t;
	}
};
