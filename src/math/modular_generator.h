#pragma once
#include "../template.h"
#include "modular.h" // modPow

// Get unique prime factors of n; O(sqrt n)
vector<ll> factorize(ll n) {
	vector<ll> fac;
	for (ll i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			while (n%i == 0) n /= i;
			fac.pb(i);
		}
	}
	if (n > 1) fac.pb(n);
	return fac;
}

// Find smallest primitive root mod n;
// time: O(sqrt(n) + g*log^2 n)
// Returns -1 if generator doesn't exist.
// For n <= 10^7 smallest generator is <= 115.
// You can use faster factorization algorithm
// to get rid of sqrt(n).
ll generator(ll n) {
	if (n <= 1 || (n > 4 && n%4 == 0)) return -1;

	vector<ll> fac = factorize(n);
	if (sz(fac) > (fac[0] == 2)+1) return -1;

	ll phi = n;
	each(p, fac) phi = phi / p * (p-1);
	fac = factorize(phi);

	for (ll g = 1;; g++) if (__gcd(g, n) == 1) {
		each(f, fac) if (modPow(g, phi/f, n) == 1)
			goto nxt;
		return g;
		nxt:;
	}
}
