#pragma once
#include "../template.h"

// Modular arithmetic for modulus < 2^62

ll modAdd(ll x, ll y, ll m) {
	x += y;
	return x < m ? x : x-m;
}

ll modSub(ll x, ll y, ll m) {
	x -= y;
	return x >= 0 ? x : x+m;
}

// About 4x slower than normal modulo
ll modMul(ll a, ll b, ll m) {
	ll c = ll((long double)a * b / m);
	ll r = (a*b - c*m) % m;
	return r < 0 ? r+m : r;
}

ll modPow(ll x, ll e, ll m) {
	ll t = 1;
	while (e) {
		if (e & 1) t = modMul(t, x, m);
		e >>= 1;
		x = modMul(x, x, m);
	}
	return t;
}
