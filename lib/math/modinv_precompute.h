#pragma once
#include "../template.h"

constexpr ll MOD = 234567899;
vector<ll> modInv(MOD); // You can lower size

// Precompute modular inverses; time: O(MOD)
void initModInv() {
	modInv[1] = 1;
	rep(i, 2, sz(modInv)) modInv[i] =
		(MOD - (MOD/i) * modInv[MOD%i]) % MOD;
}
