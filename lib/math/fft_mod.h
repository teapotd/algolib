#pragma once
#include "../template.h"

constexpr ll MOD = 15*(1<<27)+1; // ~2e9
constexpr ll ROOT = 440564289; // order = 1<<27

ll modInv(ll a, ll m) {
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}

// Compute DFT over integers mod MOD; O(n lg n)
// DFT is in bit-reversed order!
// Input size must be power of 2!
template<int dir> // 1 for DFT, -1 for inverse
void fft(vector<ll>& buf) {
	assert(__builtin_popcount(sz(buf)) == 1);
	int n = sz(buf), bits = 31-__builtin_clz(n);
	int i = (dir > 0 ? 0 : bits-1);

	vector<ll> bases = {1};
	ll c = ROOT;
	rep(k, bits, 27) c = c*c % MOD;
	rep(k, 0, n) bases.pb(bases.back()*c % MOD);

	for (; i >= 0 && i < bits; i += dir) {
		int shift = 1 << (bits-i-1);
		rep(j, 0, 1 << i) rep(k, 0, shift) {
			int a = (j << (bits-i)) | k, b = a|shift;
			auto v1 = buf[a], v2 = buf[b];
			auto base = bases[(dir*(k<<i)) & (n-1)];
			if (dir > 0) {
				buf[b] = (v1-v2)*base % MOD;
			} else {
				v2 *= base;
				buf[b] = (v1-v2) % MOD;
			}
			buf[a] = (v1+v2) % MOD;
		}
	}

	if (dir < 0) {
		ll y = modInv(n, MOD);
		each(x, buf) x = x*y % MOD;
	}
	each(x, buf) if (x < 0) x += MOD;
}

// Convolve a and b, store result in a;
// time: O(n lg n)
void convolve(vector<ll>& a, vector<ll> b) {
	int len = sz(a) + sz(b) - 1;
	int n = 1 << (32 - __builtin_clz(len));
	a.resize(n); b.resize(n);
	fft<1>(a); fft<1>(b);
	rep(i, 0, n) a[i] = a[i]*b[i] % MOD;
	fft<-1>(a);
	a.resize(len);
}
