#pragma once
#include "../template.h"

using Pll = pair<ll, ll>;

ll egcd(ll a, ll b, ll& x, ll& y) {
	if (!a) return x=0, y=1, b;
	ll d = egcd(b%a, a, y, x);
	x -= b/a*y;
	return d;
}

// Chinese Remainder Theoerem; time: O(lg lcm)
// Solves x = a.x (mod a.y), x = b.x (mod b.y)
// Returns pair (x mod lcm, lcm(a.y, b.y))
// or (-1, -1) if there's no solution.
// WARNING: a.x and b.x are assumed to be
// in [0;a.y) and [0;b.y) respectively.
// Works properly if lcm(a.y, b.y) < 2^63.
Pll crt(Pll a, Pll b) {
	if (a.y < b.y) swap(a, b);
	ll x, y, g = egcd(a.y, b.y, x, y);
	ll c = b.x-a.x, d = b.y/g, p = a.y*d;
	if (c % g) return {-1, -1};
	ll s = (a.x + c/g*x % d * a.y) % p;
	return {s < 0 ? s+p : s, p};
}
