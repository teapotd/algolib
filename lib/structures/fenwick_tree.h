#pragma once
#include "../template.h"

// Binary Indexed Tree (Fenwick tree)
// Time complexity: query O(lg n), add O(lg n)

template<class T> struct Fenwick {
	vector<T> s;
	Fenwick(int n) : s(n) {}

	void add(int i, T v) {
		for (; i < sz(s); i |= i+1) s[i] += v;
	}

	T sum(int i) {
		T v = 0;
		for (; i > 0; i &= i-1) v += s[i];
		return v;
	}
};
