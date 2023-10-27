#pragma once
#include "../template.h"

// Point-interval segment tree
// - T - stored data type
// - ID - neutral element for query operation
// - f(a, b) - associative aggregate function
struct SegTree {
	using T = int;
	static constexpr T ID = INT_MIN;
	T f(T a, T b) { return max(a, b); }

	vector<T> V;
	int len{1};

	// Initialize tree for n elements; time: O(n)
	SegTree(int n = 0, T def = 0) {
		while (len < n) len *= 2;
		V.resize(len*2, ID);
		rep(i, 0, n) V[len+i] = def;
		for (int i = len; --i;)
			V[i] = f(V[i*2], V[i*2+1]);
	}

	// Set element `i` to `val`; time: O(lg n)
	void set(int i, T val) {
		V[i += len] = val;
		while (i /= 2) V[i] = f(V[i*2], V[i*2+1]);
	}

	// Query interval [b;e); time: O(lg n)
	T query(int b, int e) {
		b += len; e += len-1;
		if (b > e)  return ID;
		if (b == e) return V[b];
		T x = V[b], y = V[e];
		while (b/2 < e/2) {
			if (~b&1) x = f(x, V[b^1]);
			if (e&1)  y = f(V[e^1], y);
			b /= 2; e /= 2;
		}
		return f(x, y);
	}

	// Find smallest j such that
	// f(A[0],...,A[j-1]) >= val; time: O(lg n)
	// Prefixes must have non-descreasing values.
	// Returns -1 if no such prefix exists.
	int lowerBound(T val) {
		if (V[1] < val) return -1;
		T x = ID;
		int j = 1;
		while (j < len) {
			T s = f(x, V[j *= 2]);
			if (s < val) x = s, j++;
		}
		return j - len + (x < val);
	}
};
