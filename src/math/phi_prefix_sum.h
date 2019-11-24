#pragma once
#include "../template.h"
#include "phi_precompute.h"

vector<ll> phiSum; // [k] = sum from 0 to k-1

// Precompute Euler's totient prefix sums
// for small values; time: O(n lg n)
void calcPhiSum() {
	calcPhi();
	phiSum.resize(sz(phi)+1);
	rep(i, 0, sz(phi))
		phiSum[i+1] = phiSum[i] + phi[i];
}

// Get prefix sum of phi(0) + ... + phi(n-1).
// WARNING: Call calcPhiSum first!
// For n > 4*10^9, answer will overflow.
// If you wish to get answer mod M use
// commented lines.
ll getPhiSum(ll n) { // time: O(n^(2/3))
	static unordered_map<ll, ll> big;
	if (n < sz(phiSum)) return phiSum[n];
	if (big.count(--n)) return big[n];

	ll ret = n*(n+1)/2;
	// ll ret = (n%2 ? n%M * ((n+1)/2 % M)
	//               : n/2%M * (n%M+1)) % M;

	for (ll s, i = 2; i <= n; i = s+1) {
		s = n / (n/i);
		ret -= (s-i+1) * getPhiSum(n/i+1);
		// ret -= (s-i+1)%M * getPhiSum(n/i+1) % M;
	}

	// ret = (ret%M + M) % M;
	return big[n] = ret;
}
