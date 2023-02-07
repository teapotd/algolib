#pragma once
#include "../template.h"
#include "phi_precompute.h"

constexpr int MOD = 998244353;

// Precompute Euler's totient prefix sums
// for small values; time: O(n lg n)
// phiSum[k] = sum from 0 to k-1
auto phiSum = [] {
	vector<ll> s(sz(phi)+1);
	rep(i, 0, sz(phi))
		s[i+1] = (s[i] + phi[i]) % MOD;
	return s;
}();

// Get prefix sum of phi(0) + ... + phi(n-1).
// For MOD > 4*10^9, answer will overflow.
ll getPhiSum(ll n) { // time: O(n^(2/3))
	static unordered_map<ll, ll> big;
	if (n < sz(phiSum)) return phiSum[n];
	if (big.count(--n)) return big[n];

	ll ret = (n%2 ? n%MOD * ((n+1)/2 % MOD)
	              : n/2%MOD * (n%MOD+1)) % MOD;

	for (ll s, i = 2; i <= n; i = s+1) {
		s = n / (n/i);
		ret -= (s-i+1)%MOD*getPhiSum(n/i+1) % MOD;
	}

	return big[n] = ret = (ret%MOD + MOD) % MOD;
}
