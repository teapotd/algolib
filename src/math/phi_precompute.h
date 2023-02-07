#pragma once
#include "../template.h"

constexpr int MAX_PHI = 1e7;

// Precompute Euler's totients; time: O(n lg n)
vi phi = [] {
	vi p(MAX_PHI+1);
	iota(all(p), 0);
	rep(i, 2, sz(p)) if (p[i] == i)
		for (int j = i; j < sz(p); j += i)
			p[j] = p[j] / i * (i-1);
	return p;
}();
