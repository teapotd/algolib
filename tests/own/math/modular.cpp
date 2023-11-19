#include "../../../src/math/modular.h"
#include "../base_test.hpp"

void deterministic() {
	assert(Zp().x == 0);
	assert(Zp(0).x == 0);
	assert(Zp(MOD).x == 0);

	for (int i = 1; i <= 500'000; i++) {
		for (int j : {i, MOD-i}) {
			Zp a = j;
			assert(a.x == j);
			assert(Zp(-j).x == MOD-j);
			assert(Zp(MOD+j).x == j);

			Zp naivePow = 1;
			for (ll p = 0; p < 10; p++) {
				assert(naivePow.x == a.pow(p).x);
				assert(naivePow.x == modPow(a.x, p, MOD));
				naivePow *= a;
			}

			Zp inv = a.inv();
			assert(inv.x == modInv(j, MOD));
			assert(inv.x == (Zp(1)/a).x);
			assert((a*inv).x == 1);
		}
	}

	assert((Zp(5)+Zp(-1)).x == 4);
	assert((Zp(5)-Zp(-1)).x == 6);
	assert((Zp(5)*Zp(5)).x == 25);
	assert((Zp(5)*Zp(-5)).x == MOD-25);
	assert((Zp(5)/Zp(-5)).x == MOD-1);
	assert((-Zp(5)).x == MOD-5);
}

void fuzz() {
	rep(i, 0, 500'000) {
		ll a = randInt(1, MOD-1);
		ll b = randInt(1, MOD-1);
		ll x, y, d = egcd(a, b, x, y);
		assert(d == gcd(a, b));
		assert(x*a + y*b == d);
	}
}

void benchmark() {
}
