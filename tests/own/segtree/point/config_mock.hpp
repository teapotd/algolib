#pragma once

#include <cassert>
#include "../../testing_hashing.h"

// Mock implementation of segment tree config.
// The aggregate is hash of sequence of underlying elements.

#define SEGTREE_CONFIG_OVERRIDE

using T = RollingHash<948'202'992, 1'000'000'007, 1'000'000'009, 1'000'000'021>;
constexpr T ID = {};
T f(T a, T b) { return a.cat(b); }

struct Naive {
	std::vector<T> seq;

	Naive(int n = 0, T def = 0) : seq(n, def) {}

	void set(int i, T val) {
		assert(i >= 0 && i < int(seq.size()));
		seq[i] = val;
	}

	T query(int b, int e) {
		// Empty interval or within valid range.
		assert(b >= e || (b >= 0 && e <= int(seq.size())));
		b = std::max(b, 0);
		e = std::min(e, int(seq.size()));
		T ret;
		for (int i = b; i < e; i++) {
			ret = ret.cat(seq[i]);
		}
		return ret;
	}
};
