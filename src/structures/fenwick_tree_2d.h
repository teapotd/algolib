#pragma once
#include "../template.h"

// Fenwick tree 2D (BIT tree 2D); space: O(n*m)
// Default version: prefix sums 2D
// Change s to hashmap for O(q lg^2 n) memory
struct Fenwick2D {
	using T = int;
	static constexpr T ID = 0;
	T f(T a, T b) { return a+b; }

	vector<T> s;
	int w, h;

	Fenwick2D(int n = 0, int m = 0)
		: s(n*m, ID), w(n), h(m) {}

	// A[i,j] = f(A[i,j], v); time: O(lg^2 n)
	void modify(int i, int j, T v) {
		for (; i < w; i |= i+1)
			for (int k = j; k < h; k |= k+1)
				s[i*h+k] = f(s[i*h+k], v);
	}

	// Query prefix; time: O(lg^2 n)
	T query(int i, int j) {
		T v = ID;
		for (; i>0; i&=i-1)
			for (int k = j; k > 0; k &= k-1)
				v = f(v, s[i*h+k-h-1]);
		return v;
	}
};
