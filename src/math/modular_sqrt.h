#pragma once
#include "../template.h"
#include "modular.h" // modPow

// Tonelli-Shanks algorithm for modular sqrt
// modulo prime; O(lg^2 p), O(lg p) for most p
// Returns -1 if root doesn't exists or else
// returns square root x (the other one is -x).
//! Source: https://github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/ModSqrt.h
// UNTESTED
ll modSqrt(ll a, ll p) {
	a %= p;
	if (a < 0) a += p;
	if (a <= 1) return a;
	if (modPow(a, p/2, p) != 1) return -1;
	if (p%4 == 3) return modPow(a, p/4+1, p);

	ll s = p-1, n = 2;
	int r = 0, j;
	while (s%2 == 0) s /= 2, r++;
	while (modPow(n, p/2, p) != p-1) n++;

	ll x = modPow(a, (s+1)/2, p);
	ll b = modPow(a, s, p), g = modPow(n, s, p);

	for (;; r = j) {
		ll t = b;
		for (j = 0; j < r && t != 1; j++)
			t = t*t % p;
		if (!j) return x;
		ll gs = modPow(g, 1LL << (r-j-1), p);
		g = gs*gs % p;
		x = x*gs % p;
		b = b*g % p;
	}
}
