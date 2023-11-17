#pragma once

#include <cassert>
#include "../../utils.hpp"

using namespace hashing_utils;

// Mock implementation of segment tree config.
// Each element of the tree is a hash of sequence of applied updates.
// The update "appends" x, x+1, ... to hashes in the interval.
// The aggregate is simply sequence of underlying elements.

using T = RollingHash<948'202'992, 1'000'000'007, 1'000'000'009, 1'000'000'021>;
constexpr T ID = {};

struct Agg {
	std::vector<T> seq;

	void leaf() {
		seq = {ID};
	}

	void merge(const Agg& r) {
		seq.insert(seq.end(), r.seq.begin(), r.seq.end());
	}

	bool apply(T& lazy, T& x) {
		if (x != ID) {
			lazy = x.cat(lazy);
			for (T& elem : seq) {
				elem = x.cat(elem);
				x = x.offset(1);
			}
		}
		return 1;
	}
};

struct Naive {
	std::vector<T> seq;

	Naive(int n = 0) : seq(n, ID) {}

	void update(int vb, int ve, T val) {
		// Empty interval or within valid range.
		assert(vb >= ve || (vb >= 0 && ve <= int(seq.size())));
		for (int i = vb; i < ve; i++) {
			seq[i] = val.cat(seq[i]);
			val = val.offset(1);
		}
	}

	std::vector<T> query(int vb, int ve) {
		// Empty interval or within valid range.
		assert(vb >= ve || (vb >= 0 && ve <= int(seq.size())));
		if (vb >= ve) return {};
		return {seq.begin()+vb, seq.begin()+ve};
	}
};
