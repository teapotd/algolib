#pragma once
#include "../template.h"

constexpr ll MOD = 15*(1<<27)+1;

// Wrapper for modular arithmetic
struct Zp {
	ll x;
	Zp(ll a = 0) { x=a%MOD; if (x<0) x+=MOD; }
	static Zp wrap(ll a){Zp t; t.x=a; return t;}

	Zp operator+(Zp r) const {
		ll a = x+r.x;
		return wrap(a >= MOD ? a-MOD : a);
	}

	Zp operator-(Zp r) const {
		ll a = x-r.x;
		return wrap(a < 0 ? a+MOD : a);
	}

	Zp operator*(Zp r) const {
		return wrap(x*r.x % MOD);
	}

	Zp operator/(Zp r) const {
		return wrap(x*r.inv().x % MOD);
	}

	Zp operator-() const { return wrap(MOD-x); }

	// Use modInv below for composite modulus
	Zp inv() const { return pow(MOD-2); }

	Zp pow(ll e) const {
		Zp t = wrap(1), m = *this;
		while (e) {
			if (e & 1) t *= m;
			e >>= 1;
			m *= m;
		}
		return t;
	}

	#define OP(c) Zp& operator c##=(Zp r){ \
		return *this=*this c r; }
	OP(+)OP(-)OP(*)OP(/)
};

ll modInv(ll a, ll m) {
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}
