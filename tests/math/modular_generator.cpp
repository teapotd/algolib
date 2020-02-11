#include "../../src/math/modular_generator.h"
#include "../../src/math/sieve.h"
#include "../../src/math/phi_precompute.h"
#include "../testing.h"

bool isGen(ll n, ll g) {
	if (g <= 0 || g >= n) return 0;
	ll tmp = g;
	rep(i, 0, phi[n]-1) {
		if (tmp == 1) return 0;
		tmp = tmp*g % n;
	}
	return tmp == 1;
}

void findMaxG() {
	constexpr int MAX_N = 1e7;
	ll maxG = 0;
	rep(n, 1, MAX_N+1) {
		maxG = max(maxG, generator(n));
	}
	deb(maxG);
}

int main() {
	// findMaxG();
	// return 0;

	sieve();
	calcPhi();

	vector<bool> hasGen(MAX_P+1);
	hasGen[2] = hasGen[4] = 1;

	each(p, primesList) {
		if (p%2 == 0) continue;
		ll q = p;
		while (q <= MAX_P) {
			hasGen[q] = 1;
			if (q*2 <= MAX_P) hasGen[q*2] = 1;
			q *= p;
		}
	}

	rep(n, 1, MAX_P+1) {
		ll g = generator(n);
		deb(n, g, hasGen[n], isGen(n, g));

		if (hasGen[n]) {
			assert(isGen(n, g));
		} else {
			assert(g == -1);
		}
	}

	return 0;
}
