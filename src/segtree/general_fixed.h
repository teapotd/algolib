#pragma once
#include "../template.h"

// Highly configurable statically allocated
// interval-interval segment tree; space: O(n)
struct SegTree {
	// Choose/write configuration
	#include "general_config.h"

	// Root node is 1, left is i*2, right i*2+1
	vector<Agg> agg; // Aggregated data for nodes
	vector<T> lazy;  // Lazy tags for nodes
	int len = 1;     // Number of leaves

	// Initialize tree for n elements; time: O(n)
	SegTree(int n = 0) {
		while (len < n) len *= 2;
		agg.resize(len*2);
		lazy.resize(len*2, ID);
		rep(i, 0, n) agg[len+i].leaf();
		for (int i = len; --i;) pull(i);
	}

	void pull(int i) {
		(agg[i] = agg[i*2]).merge(agg[i*2+1]);
	}

	void push(int i) {
		rep(c, 0, 2)
			agg[i*2+c].apply(lazy[i*2+c], lazy[i]);
		lazy[i] = ID;
	}

	template<bool U>
	void go(int vb, int ve, int i, int b, int e,
	        auto fn) {
		if (vb < e && b < ve)
			if (b < vb || ve < e || !fn(i)) {
				int m = (b+e) / 2;
				push(i);
				go<U>(vb, ve, i*2, b, m, fn);
				go<U>(vb, ve, i*2+1, m, e, fn);
				if (U) pull(i);
			}
	}

	// Modify interval [b;e) with val; O(lg n)
	void update(int b, int e, T val) {
		go<1>(b, e, 1, 0, len, [&](int i) {
			return agg[i].apply(lazy[i], val);
		});
	}

	// Query interval [b;e); time: O(lg n)
	Agg query(int b, int e) {
		Agg t;
		go<0>(b, e, 1, 0, len, [&](int i) {
			return t.merge(agg[i]), 1;
		});
		return t;
	}

	// Find smallest `j` such that
	// g(aggregate of [0,j)) is true; O(lg n)
	// The function `g` must be monotonic.
	// Returns -1 if no such prefix exists.
	int lowerBound(auto g) {
		if (!g(agg[1])) return -1;
		Agg x, s;
		int i = 1;
		for (; i < len; g(s) || (x = s, i++))
			push(i), (s = x).merge(agg[i *= 2]);
		return i - len + !g(x);
	}
};
