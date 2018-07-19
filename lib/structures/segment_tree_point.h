#pragma once
#include "../template.h"

struct SegmentTree {
	using T = int;
	const T ID = INT_MIN;
	T merge(T a, T b) { return max(a, b); }

	vector<T> V;
	int len;

	SegmentTree(int n, T def) {
		for (len = 1; len < n; len *= 2);
		V.assign(len+n, def);
		V.resize(len*2, ID);
		for (int i = len-1; i > 0; i--) update(i);
	}

	void update(int i) {
		V[i] = merge(V[i*2], V[i*2+1]);
	}

	void set(int i, T val) {
		V[i+=len] = val;
		while ((i/=2) > 0) update(i);
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