#pragma once
#include "../template.h"
#include "sieve.h"
#include "miller_rabin.h"
#include "modular64.h"

using Factor = pair<ll, int>;

// Pollard's rho factorization algorithm
// Las Vegas version; time: n^(1/3)
// Before using, initialize sieve.
// Set MAX_P >= (max input number)^(1/3)
// Returns pairs (prime, power), sorted
vector<Factor> factorize(ll n) {
	vector<Factor> ret;
	each(p, primesList) if (n%p == 0) {
		ret.pb({ p, 0 });
		while (n%p == 0) {
			n /= p;
			ret.back().y++;
		}
	}

	if (n <= 1) return ret;
	if (isPrime(n)) {
		ret.pb({ n, 1 });
		return ret;
	}

	// Now n = p*q for some prime p and q
	for (ll a = 1;; a++) {
		ll x = 2, y = 2, d = 1;

		while (d == 1) {
			x = modAdd(modMul(x, x, n), a, n);
			y = modAdd(modMul(y, y, n), a, n);
			y = modAdd(modMul(y, y, n), a, n);
			d = __gcd(abs(x-y), n);
		}

		if (d != n) {
			n /= d;
			if (d > n) swap(d, n);
			ret.pb({ d, 1 });
			if (d == n) ret.back().y++;
			else ret.pb({ n, 1 });
			return ret;
		}
	}
}
