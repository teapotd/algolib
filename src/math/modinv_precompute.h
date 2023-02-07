#pragma once
#include "../template.h"

constexpr ll MOD = 234567899;

// Precompute modular inverses; time: O(n)
auto modInv = [] {
	vector<ll> v(MOD, 1); // You can lower size
	rep(i, 2, sz(v))
		v[i] = (MOD - (MOD/i) * v[MOD%i]) % MOD;
	return v;
}();
