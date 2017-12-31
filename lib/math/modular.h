#pragma once
#include "../template.h"

constexpr ll MOD = 2345678917;

ll modInv(ll a, ll m) {
	return (a == 1 ? 1 :
		((a - modInv(m%a, a))*m + 1) / a);
}

ll umod(ll a, ll m) {
	a %= m; return (a >= 0 ? a : a+m);
}

struct Zp {
	ll x;
	Zp(ll y) : x(umod(y, MOD)) {}

	Zp operator+(Zp r) const { return x+r.x; }
	Zp operator-(Zp r) const { return x-r.x; }
	Zp operator*(Zp r) const { return x*r.x; }
	Zp operator/(Zp r) const {
		return x*r.inv().x;
	}

	Zp inv() { return modInv(x, MOD); }

	Zp pow(ll e) {
		if (!e) return 1;
		Zp t = pow(e/2);
		return t*t * (e & 1 ? x : 1);
	}

	void print() { cerr << x; }
};
