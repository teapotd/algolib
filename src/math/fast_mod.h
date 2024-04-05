#pragma once
#include "../template.h"

using ull = uint64_t;

// Compute a % b faster, where b is constant,
// but not known at compile time.
// Returns value in range [0,2b).
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/various/FastMod.h
struct FastMod {
	ull b, m;
	FastMod(ull a) : b(a), m(-1ULL / a) {}
	ull operator()(ull a) { // a % b + (0 or b)
		return a - ull((__uint128_t(m)*a)>>64) * b;
	}
};
