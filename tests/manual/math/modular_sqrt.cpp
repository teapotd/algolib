#include "../../../src/math/modular_sqrt.h"
#include "../../../src/math/sieve.h"
#include "../testing.h"

void check(ll p) {
	vector<ll> sqr(p, -1);
	rep(i, 0, p) sqr[i*i % p] = i;

	rep(i, 0, p) {
		ll k = modSqrt(i, p);
		if (sqr[i] == -1) {
			assert(k == -1);
		} else {
			assert(k == sqr[i] || p-k == sqr[i]);
		}
	}
}

int main() {
	sieve();
	each(p, primesList) {
		if (p >= 5000) break;
		check(p);
	}
	return 0;
}
