#pragma once
#include "../template.h"
#include "phi_precompute.h"

constexpr int MOD = 998244353;

vector<ll> phiSum; // [k] = sum from 0 to k-1

// Precompute Euler's totient prefix sums
// for small values; time: O(n lg n)
void calcPhiSum() {
	calcPhi();
	phiSum.resize(sz(phi)+1);
	rep(i, 0, sz(phi))
		phiSum[i+1] = (phiSum[i] + phi[i]) % MOD;
}

// Get prefix sum of phi(0) + ... + phi(n-1).
// WARNING: Call calcPhiSum first!
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
