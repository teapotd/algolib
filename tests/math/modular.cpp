#include "../../lib/math/modular.h"
#include "../testing.h"

ll naivePow(ll a, ll p) {
	ll ret = 1;
	for (int i = 0; i < p; i++) {
		ret = (ret*a) % MOD;
	}
	return ret;
}

int main() {
	assert(Zp(-3243245).x >= 0);

	for (Zp a = 1; a.x <= 1000000; a.x++) {
		Zp inv = a.inv();
		assert(inv.x == (Zp(1)/a).x);
		assert((a*inv).x == 1);

		for (ll p = 0; p < 10; p++) {
			assert(naivePow(a.x, p) == a.pow(p).x);
		}

		assert((a * -50).x >= 0);
		assert((a - (a + 5)).x >= 0);
		assert((a - 100).x >= 0);
	}

	Zp test = -5;
	deb(test);
	return 0;
}
