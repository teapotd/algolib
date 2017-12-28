#pragma once
#include "../template.h"

// Binary Indexed Tree (Fenwick tree)
// Time complexity:
// - modify point:         O(lg n)
// - query interval [0;i): O(lg n)

template<class T> struct Fenwick {
	vector<T> s;
	Fenwick(int n) : s(n, 0) {}                // Change here identity

	void modify(int i, T v) {
		for (; i < sz(s); i |= i+1) s[i] += v; // Change here operation
	}

	T query(int i) {
		T v = 0;
		for (; i > 0; i &= i-1) v += s[i-1];   // Change here operation
		return v;
	}
};
