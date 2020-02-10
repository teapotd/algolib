#pragma once
#include "../template.h"

constexpr int MOD = 1e9+7;

ll modInv(ll a, ll m) { // a^(-1) mod m
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}

// Find shortest linear recurrence that matches
// given starting terms of recurrence; O(n^2)
// Returns vector C such that for each i >= |C|
// A[i] = sum A[i-j-1]*C[j] for j = 0..|C|-1
// UNTESTED
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/BerlekampMassey.h
vector<ll> massey(vector<ll>& A) {
	int n = sz(A), len = 0, k = 0;
	ll s = 1;
	vector<ll> B(n), C(n), tmp;
	B[0] = C[0] = 1;

	rep(i, 0, n) {
		ll d = 0;
		k++;
		rep(j, 0, len+1)
			d = (d + C[j] * A[i-j]) % MOD;

		if (d) {
			ll q = d * modInv(s, MOD) % MOD;
			tmp = C;

			rep(j, k, n)
				C[j] = (C[j] - q * B[j-k]) % MOD;

			if (len*2 <= i) {
				B.swap(tmp);
				len = i-len+1;
				s = d + (d < 0) * MOD;
				k = 0;
			}
		}
	}

	C.resize(len+1);
	C.erase(C.begin());
	each(x, C) x = (MOD - x) % MOD;
	return C;
}
