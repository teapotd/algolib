#pragma once
#include "../template.h"
#include "modular64.h"
#include "miller_rabin.h"

using Factor = pair<ll, int>;

void rho(vector<ll>& out, ll n) {
	if (n <= 1) return;
	if (isPrime(n)) out.pb(n);
	else if (n%2 == 0) rho(out,2), rho(out,n/2);
	else for (ll a = 2;; a++) {
		ll x = 2, y = 2, d = 1;
		while (d == 1) {
			x = modAdd(modMul(x, x, n), a, n);
			y = modAdd(modMul(y, y, n), a, n);
			y = modAdd(modMul(y, y, n), a, n);
			d = __gcd(abs(x-y), n);
		}
		if (d != n) {
			rho(out, d);
			rho(out, n/d);
			return;
		}
	}
}

// Pollard's rho factorization algorithm
// Las Vegas version; time: n^(1/4)
// Returns pairs (prime, power), sorted
vector<Factor> factorize(ll n) {
	vector<Factor> ret;
	vector<ll> raw;
	rho(raw, n);
	sort(all(raw));
	each(f, raw) {
		if (ret.empty() || ret.back().x != f)
			ret.pb({ f, 1 });
		else
			ret.back().y++;
	}
	return ret;
}
