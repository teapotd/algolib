#pragma once
#include "../template.h"

// Segment tree (point, interval)
// Configure by modifying:
// - T - stored data type
// - ID - neutral element for query operation
// - f(a, b) - combine results
struct SegTree {
	using T = int;
	T ID = INT_MIN;
	T f(T a, T b) { return max(a,b); }

	vector<T> V;
	int len;

	// Initialize tree for n elements; time: O(n)
	SegTree(int n = 0, T def = 0) {
		for (len = 1; len < n; len *= 2);
		V.resize(len*2, ID);
		rep(i, 0, n) V[len+i] = def;
		for (int i = len; --i;)
			V[i] = f(V[i*2], V[i*2+1]);
	}

	// Set element `i` to `val`; time: O(lg n)
	void set(int i, T val) {
		V[i += len] = val;
		while (i /= 2)
			V[i] = f(V[i*2], V[i*2+1]);
	}

	// Query interval [b;e); time: O(lg n)
	T query(int b, int e) {
		b += len; e += len-1;
		if (b > e)  return ID;
		if (b == e) return V[b];
		T x = f(V[b], V[e]);

		while (b/2 < e/2) {
			if (~b&1) x = f(x, V[b^1]);
			if (e&1)  x = f(x, V[e^1]);
			b /= 2; e /= 2;
		}
		return x;
	}
};
