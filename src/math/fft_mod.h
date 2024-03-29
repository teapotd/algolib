#pragma once
#include "../template.h"
#define modPow modPow2 //!HIDE
#define egcd egcd2     //!HIDE

// Number Theoretic Tranform (NTT)
// For functions below you can choose 2 params:
// 1. M - prime modulus that MUST BE of form
//        a*2^k+1, computation is done in Z_M
// 2. R - generator of Z_M

// Modulus often seen on Codeforces:
// M = (119<<23)+1, R = 62; M is 998244353

// Parameters for ll computation with CRT:
// M = (479<<21)+1, R = 62; M is > 10^9
// M = (483<<21)+1, R = 62; M is > 10^9

ll modPow(ll a, ll e, ll m) {
	ll t = 1 % m;
	while (e) {
		if (e % 2) t = t*a % m;
		e /= 2; a = a*a % m;
	}
	return t;
}

// Compute DFT over Z_M with generator R.
// Input size must be power of 2; O(n lg n)
// Input is expected to be in range [0;MOD)!
// dit == true <=> inverse transform * 2^n
//                 (without normalization)
template<ll M, ll R, bool dit>
void ntt(vector<ll>& a) {
	static vector<ll> w(2, 1);
	int n = sz(a);

	for (int k = sz(w); k < n; k *= 2) {
		w.resize(n, 1);
		ll c = modPow(R, M/2/k, M);
		if (dit) c = modPow(c, M-2, M);
		rep(i, k+1, k*2) w[i] = w[i-1]*c % M;
	}

	for (int t = 1; t < n; t *= 2) {
		int k = (dit ? t : n/t/2);
		for (int i=0; i < n; i += k*2) rep(j,0,k) {
			ll &c = a[i+j], &d = a[i+j+k];
			ll e = w[j+k], f = d;
			d = (dit ? c - (f=f*e%M) : (c-f)*e % M);
			if (d < 0) d += M;
			if ((c += f) >= M) c -= M;
		}
	}
}

// Convolve a and b mod M (R is generator),
// store result in a; time: O(n lg n), 3x NTT
// Input is expected to be in range [0;MOD)!
template<ll M = (119<<23)+1, ll R = 62>
void convolve(vector<ll>& a, vector<ll> b) {
	int len = sz(a) + sz(b) - 1;
	if (len <= 0) return a.clear();
	int n = 2 << __lg(len);
	ll t = modPow(n, M-2, M);
	a.resize(n); b.resize(n);
	ntt<M,R,0>(a); ntt<M,R,0>(b);
	rep(i, 0, n) a[i] = a[i]*b[i] % M * t % M;
	ntt<M,R,1>(a);
	a.resize(len);
}

ll egcd(ll a, ll b, ll& x, ll& y) {
	if (!a) return x=0, y=1, b;
	ll d = egcd(b%a, a, y, x);
	x -= b/a*y;
	return d;
}

// Convolve a and b with 64-bit output,
// store result in a; time: O(n lg n), 6x NTT
// Input is expected to be non-negative!
void convLong(vector<ll>& a, vector<ll> b) {
	const ll M1 = (479<<21)+1, M2 = (483<<21)+1;
	const ll MX = M1*M2, R = 62;

	auto c = a, d = b;
	each(k, a) k %= M1;
	each(k, b) k %= M1;
	each(k, c) k %= M2;
	each(k, d) k %= M2;

	convolve<M1, R>(a, b);
	convolve<M2, R>(c, d);

	ll x, y; egcd(M1, M2, x, y);

	rep(i, 0, sz(a)) {
		a[i] += (c[i]-a[i])*x % M2 * M1;
		if ((a[i] %= MX) < 0) a[i] += MX;
	}
}

// Big-integer multiplication note:
// - use convLong with base 10^6 for n < 10^6
// - use convLong with base 10^5 for n < 10^8
