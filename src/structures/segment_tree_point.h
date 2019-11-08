#pragma once
#include "../template.h"

// Segment tree (point, interval)
// Configure by modifying:
// - T - stored data type
// - ID - neutral element for query operation
// - merge(a, b) - combine results
struct SegmentTree {
	using T = int;
	static constexpr T ID = INT_MIN;
	static T merge(T a, T b) { return max(a,b); }

	vector<T> V;
	int len;

	SegmentTree(int n = 0, T def = ID) {
		for (len = 1; len < n; len *= 2);
		V.resize(len*2, ID);
		rep(i, 0, n) V[len+i] = def;
		for (int i = len-1; i > 0; i--)
			V[i] = merge(V[i*2], V[i*2+1]);
	}

	void set(int i, T val) {
		V[i+=len] = val;
		while ((i/=2) > 0)
			V[i] = merge(V[i*2], V[i*2+1]);
	}

	T query(int begin, int end) {
		begin += len; end += len-1;
		if (begin > end)  return ID;
		if (begin == end) return V[begin];
		T x = merge(V[begin], V[end]);

		while (begin/2 < end/2) {
			if (~begin&1) x = merge(x, V[begin^1]);
			if (end&1)    x = merge(x, V[end^1]);
			begin /= 2; end /= 2;
		}
		return x;
	}
};

constexpr SegmentTree::T SegmentTree::ID;