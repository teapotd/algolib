#pragma once
#include "../template.h"

// Big prime number, about 2*10^9
constexpr int MOD = 15*(1<<27)+1;

ll modInv(ll a, ll m) { // a^(-1) mod m
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}

ll modPow(ll a, ll e, ll m) { // a^e mod m
	ll t = 1 % m;
	while (e) {
		if (e % 2) t = t*a % m;
		e /= 2; a = a*a % m;
	}
	return t;
}

// Wrapper for modular arithmetic
struct Zp {
	ll x; // Contained value, in range [0;MOD-1]
	Zp() {}
	Zp(ll a) : x(a%MOD) { if (x < 0) x += MOD; }

	#define OP(c,d) Zp& operator c##=(Zp r) { \
			x = x d; return *this; } \
		Zp operator c(Zp r) const { \
			Zp t = *this; return t c##= r; }

	OP(+, +r.x - MOD*(x+r.x >= MOD));
	OP(-, -r.x + MOD*(x-r.x < 0));
	OP(*, *r.x % MOD);
	OP(/, *r.inv().x % MOD);

	// For composite modulus use modInv, not pow
	Zp inv() const { return pow(MOD-2); }
	Zp pow(ll e) const{ return modPow(x,e,MOD); }
	void print() { cerr << x; } // For deb()
};

// Extended Euclidean Algorithm
ll egcd(ll a, ll b, ll& x, ll& y) {
	if (!a) return x=0, y=1, b;
	ll d = egcd(b%a, a, y, x);
	x -= b/a*y;
	return d;
}
