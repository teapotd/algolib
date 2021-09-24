#pragma once
#include "../template.h"

constexpr ll MOD = 998244353;

using Poly = vector<ll>;

// Compute k-th term of an n-order linear
// recurrence C[i] = sum C[i-j-1]*D[j],
// given C[0..n-1] and D[0..n-1]; O(n^2 log k)
//! Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/LinearRecurrence.h
ll linearRec(const Poly& C,
             const Poly& D, ll k) {
	int n = sz(D);

	auto mul = [&](Poly a, Poly b) {
		Poly ret(n*2+1);
		rep(i, 0, n+1) rep(j, 0, n+1)
			ret[i+j] = (ret[i+j] + a[i]*b[j]) % MOD;
		for (int i = n*2; i > n; i--) rep(j, 0, n)
			ret[i-j-1] =
				(ret[i-j-1] + ret[i]*D[j]) % MOD;
		ret.resize(n+1);
		return ret;
	};

	Poly pol(n+1), e(n+1);
	pol[0] = e[1] = 1;

	for (k++; k; k /= 2) {
		if (k % 2) pol = mul(pol, e);
		e = mul(e, e);
	}

	ll ret = 0;
	rep(i,0,n) ret = (ret + pol[i+1]*C[i]) % MOD;
	return ret;
}
