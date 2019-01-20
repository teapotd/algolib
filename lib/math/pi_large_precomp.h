#pragma once
#include "../template.h"
#include "sieve.h"

// Count primes in given interval
// using precomputed table.
// Set MAX_P to sqrt(MAX_N) and run sieve()!
// Precomputed table will contain N_BUCKETS
// elements - check source size limit.

constexpr ll MAX_N = 1e11+1;
constexpr ll N_BUCKETS = 10000;
constexpr ll BUCKET_SIZE = (MAX_N/N_BUCKETS)+1;
constexpr ll precomputed[] = {/* ... */};

ll sieveRange(ll from, ll to) {
	bitset<BUCKET_SIZE> elems;
	from = max(from, 2LL);
	to = max(from, to);
	each(p, primesList) {
		ll c = max((from+p-1) / p, 2LL);
		for (ll i = c*p; i < to; i += p)
			elems.set(i-from);
	}
	return to-from-elems.count();
}

// Run once on local computer to precompute
// table. Takes about 10 minutes for n = 1e11.
// Sanity check (for default params):
// 664579, 606028, 587253, 575795, ...
void localPrecompute() {
	for (ll i = 0; i < MAX_N; i += BUCKET_SIZE) {
		ll to = min(i+BUCKET_SIZE, MAX_N);
		cout << sieveRange(i, to) << ',' << flush;
	}
	cout << endl;
}

// Count primes in [from;to) using table.
// O(N_BUCKETS + BUCKET_SIZE*lg lg n + sqrt(n))
ll countPrimes(ll from, ll to) {
	ll bFrom = from/BUCKET_SIZE+1,
	   bTo = to/BUCKET_SIZE;
	if (bFrom > bTo) return sieveRange(from, to);
	ll ret = accumulate(precomputed+bFrom,
	                    precomputed+bTo, 0);
	ret += sieveRange(from, bFrom*BUCKET_SIZE);
	ret += sieveRange(bTo*BUCKET_SIZE, to);
	return ret;
}
