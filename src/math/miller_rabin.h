#pragma once
#include "../template.h"
#include "modular64.h"

// Miller-Rabin primality test
// time O(k*lg^2 n), where k = number of bases

// Deterministic for p <= 10^9
// constexpr ll BASES[] = {
//   336781006125, 9639812373923155
// };

// Deterministic for p <= 2^64
constexpr ll BASES[] = {
	2,325,9375,28178,450775,9780504,1795265022
};

bool isPrime(ll p) {
	if (p <= 2) return p == 2;
	if (p%2 == 0) return 0;

	ll d = p-1, t = 0;
	while (d%2 == 0) d /= 2, t++;

	each(a, BASES) if (a%p) {
		// ll a = rand() % (p-1) + 1;
		ll b = modPow(a%p, d, p);
		if (b == 1 || b == p-1) continue;
		rep(i, 1, t)
			if ((b = modMul(b, b, p)) == p-1) break;
		if (b != p-1) return 0;
	}

	return 1;
}
