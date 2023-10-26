#pragma once
#include "../template.h"

// Bitset with fast predecessor and successor
// queries. Can handle 50-200mln operations
// per second. Assumes X86 shift overflows.
template<int N>
struct IntSet {
	uint64_t V[N/64+1] = {};
	IntSet<(N < 65 ? 0 : N/64+1)> up;

	// Is `i` contained in the set?
	bool has(int i) const {
		return (V[i/64] >> i) & 1;
	}

	// Add `i` to the set.
	void add(int i) {
		if (!V[i/64]) up.add(i/64);
		V[i/64] |= 1ull << i;
	}

	// Delete `i` from the set.
	void del(int i) {
		if (!(V[i/64] &= ~(1ull<<i))) up.del(i/64);
	}

	// Find first element > i, or return -1.
	// `i` must be in range [0;N).
	int next(int i) {
		auto x = V[i/64] >> i;
		if (x &= ~1) return i+__builtin_ctzll(x);
		return (i = up.next(i/64)) < 0 ? i :
			i*64+__builtin_ctzll(V[i]);
	}

	// Find last element < i, or return -1.
	// `i` must be in range [0;N).
	int prev(int i) {
		auto x = V[i/64] << (63-i);
		if (x &= INT64_MAX)
			return i-__builtin_clzll(x);
		return (i = up.prev(i/64)) < 0 ? i :
			i*64+63-__builtin_clzll(V[i]);
	}
};

template<>
struct IntSet<0> {
	void add(int) {}
	void del(int) {}
	int next(int) { return -1; }
	int prev(int) { return -1; }
};
