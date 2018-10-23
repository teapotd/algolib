#pragma once
#include "../template.h"

constexpr ll MOD = 15*(1<<27)+1;

// Wrapper for modular arithmetic
struct Zp {
	ll x;
	Zp(ll a = 0) {
		if (a < 0) a = a%MOD + MOD;
		else if (a >= MOD*2) a %= MOD;
		else if (a >= MOD) a -= MOD;
		x = a;
	}

	Zp operator+(Zp r) const{ return x+r.x; }
	Zp operator-(Zp r) const{ return x-r.x+MOD; }
	Zp operator*(Zp r) const{ return x*r.x; }
	Zp operator/(Zp r) const{return x*r.inv().x;}
	Zp operator-()     const{ return MOD-x; }

	// Use modInv below for composite modulus
	Zp inv() const { return pow(MOD-2); }

	Zp pow(ll e) const {
		Zp t = 1, m = *this;
		while (e) {
			if (e & 1) t = t*m;
			e >>= 1; m = m*m;
		}
		return t;
	}

	#define OP(c) Zp& operator c##=(Zp r){ \
		return *this=*this c r; }
	OP(+)OP(-)OP(*)OP(/)
	void print() { cerr << x; }
};

ll modInv(ll a, ll m) {
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}
