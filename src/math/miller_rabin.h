#pragma once
#include "../template.h"
#include "modular64.h"

// Miller-Rabin primality test
// time O(k*lg^2 n), where k = number of bases

// Deterministic for p <= 1'050'535'501
// constexpr ll BASES[] = {
//   336'781'006'125, 9'639'812'373'923'155
// };

// Deterministic for p <= 2^64
constexpr ll BASES[] = {
	2, 325, 9'375, 28'178,
	450'775, 9'780'504, 1'795'265'022
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
