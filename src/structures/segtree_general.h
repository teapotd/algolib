#pragma once
#include "../template.h"

// Highly configurable statically allocated
// (interval; interval) segment tree;
// space: O(n)
struct SegTree {
	// Choose/write configuration
	#include "segtree_config.h"

	// Root node is 1, left is i*2, right i*2+1
	vector<Agg> agg; // Aggregated data for nodes
	vector<T> lazy;  // Lazy tags for nodes
	int len{1};      // Number of leaves

	// Initialize tree for n elements; time: O(n)
	SegTree(int n = 0) {
		while (len < n) len *= 2;
		agg.resize(len*2);
		lazy.resize(len*2, ID);
		rep(i, 0, n) agg[len+i].leaf();
		for (int i = len; --i;)
			(agg[i] = agg[i*2]).merge(agg[i*2+1]);
	}

	void push(int i, int s) {
		if (T& x = lazy[i]; x != ID) {
			rep(c, 0, 2)
				agg[i*2+c].apply(lazy[i*2+c], x, s/2);
			x = ID;
		}
	}

	// Modify interval [vb;ve) with val; O(lg n)
	T update(int vb, int ve, T val, int i = 1,
	         int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (vb >= e || b >= ve) return val;

		if (b >= vb && e <= ve &&
		    agg[i].apply(lazy[i], val, e-b))
			return val;

		int m = (b+e) / 2;
		push(i, e-b);
		val = update(vb, ve, val, i*2, b, m);
		val = update(vb, ve, val, i*2+1, m, e);
		(agg[i] = agg[i*2]).merge(agg[i*2+1]);
		return val;
	}

	// Query interval [vb;ve); time: O(lg n)
	Agg query(int vb, int ve, int i = 1,
	          int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (vb >= e || b >= ve) return {};
		if (b >= vb && e <= ve) return agg[i];

		int m = (b+e) / 2;
		push(i, e-b);
		Agg t = query(vb, ve, i*2, b, m);
		t.merge(query(vb, ve, i*2+1, m, e));
		return t;
	}

	// Find smallest `j` such that
	// f(aggregate of [0,j)) is true; O(lg n)
	// The function `f` must be monotonic.
	// Returns -1 if no such prefix exists.
	int lowerBound(auto f) {
		if (!f(agg[1])) return -1;
		Agg x, s;
		int i = 1, k = len;
		while (i < len) {
			push(i, k);
			(s = x).merge(agg[i *= 2]);
			if (!f(s)) x = s, i++;
			k /= 2;
		}
		return i - len + !f(x);
	}
};
