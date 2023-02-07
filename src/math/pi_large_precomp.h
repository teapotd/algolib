#pragma once
#include "../template.h"
#include "sieve.h"

// Count primes in given interval
// using precomputed table.
// Set MAX_P to sqrt(MAX_N)!
// Precomputed table will contain N_BUCKETS
// elements - check source size limit.
// If you need to pack more values,
// you can use `utils/packing.h`.

// Precomputed table size:
//   MAX_N=1e11, N_BUCKETS=1e4 -> 43.96 KB
//   MAX_N=1e11, N_BUCKETS=2e4 -> 85.55 KB

constexpr ll MAX_N = 1e11;
constexpr ll N_BUCKETS = 2e4;
constexpr ll BUCKET_SIZE = (MAX_N/N_BUCKETS)+1;
#ifndef PRECOMPUTED_DEFINED //!HIDE
constexpr ll precomputed[] = {/* ... */};
#endif //!HIDE

// Unpack precomputed data.
vector<ll> buckets = [] {
	vector<ll> ret(N_BUCKETS+1);
	ll d = 0;
	rep(i, 0, N_BUCKETS)
		ret[i+1] = ret[i] + (d += precomputed[i]);
	return ret;
}();

// Count primes in range [b;e) naively.
ll sieveRange(ll b, ll e) {
	bitset<BUCKET_SIZE> elems;
	b = max(b, 2LL);
	e = max(b, e);
	each(p, primesList) {
		ll c = max((b+p-1) / p, 2LL);
		for (ll i = c*p; i < e; i += p)
			elems.set(i-b);
	}
	return e-b-elems.count();
}

// Run once on local computer to precompute
// table. Takes about 10 minutes for n = 1e11.
// First and last values for default params:
// 348513, -32447, -9941, -6221, -4585,
// ..., -162, -162, 563, -286, -949
void localPrecompute() {
	ll last = 0;
	for (ll i = 0; i <= MAX_N; i += BUCKET_SIZE) {
		ll to = min(i+BUCKET_SIZE, MAX_N+1);
		ll cur = sieveRange(i, to);
		cout << cur-last << ',' << flush;
		last = cur;
	}
	cout << endl;
}

// Count number of primes <= x;
// time: O(BUCKET_SIZE*lg lg n + sqrt(n)/lg(n))
ll pi(ll x) {
	ll b = x/BUCKET_SIZE, j = b*BUCKET_SIZE;
	return buckets[b] + sieveRange(j, x+1);
}
