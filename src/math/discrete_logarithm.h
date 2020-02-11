#pragma once
#include "../template.h"

ll modInv(ll a, ll m) { // a^(-1) mod m
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}

// Baby-step giant-step algorithm; O(sqrt(p))
// Finds smallest x such that a^x = b (mod p)
// or returns -1 if there's no solution.
ll dlog(ll a, ll b, ll p) {
	int m = int(min(ll(sqrt(p))+2, p-1));
	unordered_map<ll, int> small;
	ll t = 1;

	rep(i, 0, m) {
		int& k = small[t];
		if (!k) k = i+1;
		t = t*a % p;
	}

	t = modInv(t, p);

	rep(i, 0, m) {
		int j = small[b];
		if (j) return i*m + j - 1;
		b = b*t % p;
	}

	return -1;
}
