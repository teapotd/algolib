#include "../../lib/math/modular.h"
#include "../testing.h"

ll naivePow(ll a, ll p) {
	ll ret = 1;
	for (int i = 0; i < p; i++) {
		ret = (ret*a) % MOD;
	}
	return ret;
}

ll gcd(ll a, ll b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

void testExtGcd() {
	rep(i, 0, 1000000) {
		ll a = r(1, 1e9);
		ll b = r(1, 1e9);
		ll x, y, d = egcd(a, b, x, y);
		assert(d == gcd(a, b));
		assert(x*a + y*b == d);
	}
}

int main() {
	testExtGcd();
	assert(Zp(-3243245).x >= 0);

	for (Zp a = 1; a.x <= 3000000; a.x++) {
		Zp inv = a.inv();
		assert(inv.x == (Zp(1)/a).x);
		assert((a*inv).x == 1);

		for (ll p = 0; p < 10; p++) {
			ll naive = naivePow(a.x, p);
			assert(naive == a.pow(p).x);
			assert(naive == modPow(a.x, p, MOD));
		}

		assert((a * -50).x >= 0);
		assert((a - (a + 5)).x >= 0);
		assert((a - 100).x >= 0);
	}

	Zp test = -5;
	deb(test);
	return 0;
}
