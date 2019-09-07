#pragma once
#include "../template.h"

// Big prime number, about 2*10^9
constexpr ll MOD = 15*(1<<27)+1;

ll modInv(ll a, ll m) { // a^(-1) mod m
	if (a == 1) return 1;
	return ((a - modInv(m%a, a))*m + 1) / a;
}

ll modPow(ll a, ll e, ll m) { // a^e mod m
	ll t = 1 % m;
	while (e) {
		if (e & 1) t = t*a % m;
		e >>= 1; a = a*a % m;
	}
	return t;
}

// Wrapper for modular arithmetic
struct Zp {
	ll x; // Contained value, in range [0;MOD-1]
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
	Zp pow(ll e) const{ return modPow(x,e,MOD); }

	// For composite modulus use modInv, not pow
	Zp inv() const { return pow(MOD-2); }

	#define OP(c) Zp& operator c##=(Zp r){ \
		return *this=*this c r; }
	OP(+)OP(-)OP(*)OP(/)
	void print() { cerr << x; }
};
