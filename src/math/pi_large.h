#pragma once
#include "../template.h"
//! Source: https://acgan.sh/posts/2016-12-23-prime-counting.html

// Precompute prime counting function
// for small values; time: O(n lg lg n)
vector<ll> prl, pis = [] {
	constexpr int MAX_P = 1e7;
	vector<ll> p(MAX_P+1, 1);
	p[0] = p[1] = 0;

	for (int i = 2; i*i <= MAX_P; i++) if (p[i])
		for (int j = i*i; j <= MAX_P; j += i)
			p[j] = 0;

	rep(i, 1, sz(p)) {
		if (p[i]) prl.pb(i);
		p[i] += p[i-1];
	}
	return p;
}();

ll partial(ll x, ll a) {
	static vector<unordered_map<ll, ll>> big;
	big.resize(sz(prl));
	if (!a) return (x+1) / 2;
	if (big[a].count(x)) return big[a][x];
	ll ret = partial(x, a-1)
		- partial(x / prl[a], a-1);
	return big[a][x] = ret;
}

// Count number of primes <= x;
// time: O(n^(2/3) * log(n)^(1/3))
// Set MAX_P to be > sqrt(x) before using!
ll pi(ll x) {
	static unordered_map<ll, ll> big;
	if (x < sz(pis)) return pis[x];
	if (big.count(x)) return big[x];

	ll a = 0;
	while (prl[a]*prl[a]*prl[a]*prl[a] < x) a++;

	ll ret = 0, b = --a;

	while (++b < sz(prl) && prl[b]*prl[b] < x) {
		ll w = x / prl[b];
		ret -= pi(w);
		for (ll j = b; prl[j]*prl[j] <= w; j++)
			ret -= pi(w / prl[j]) - j;
	}

	ret += partial(x, a) + (b+a-1)*(b-a)/2;
	return big[x] = ret;
}
