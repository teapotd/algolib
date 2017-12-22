#pragma once
#include "../template.h"

constexpr ll MOD = 234567899;

// Compute modular inverse of a mod b [UNTESTED]
ll modInv(ll a, ll m) { return (a == 1 ? 1 : ((a - modInv(m%a, a))*m + 1) / a); }

// Integer mod p container [UNTESTED]
struct Zp {
	ll x;
	Zp(ll y) : x(y % MOD) {}

	Zp operator+(Zp r) const { return x+r.x; }
	Zp operator-(Zp r) const { return x-r.x; }
	Zp operator*(Zp r) const { return x*r.x; }
	Zp operator/(Zp r) const { return x*modInv(r.x, MOD); }

	Zp inv() { return modInv(x, MOD); }

	Zp pow(ll e) {
		if (!e) return 1;
		Zp t = pow(e/2);
		return t*t * (e % 2 ? x : 1);
	}
};