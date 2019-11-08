#include "../../src/math/sieve_factors.h"
#include "../../src/math/miller_rabin.h"
#include "../testing.h"

void check(ll n) {
    auto factors = factorize(n);
    ll mult = 1;
    // deb(n, factors);

    rep(i, 0, sz(factors)) {
      auto f = factors[i];

      if (i > 0) assert(factors[i-1].x < f.x);
      assert(isPrime(f.x));
      rep(j, 0, f.y) mult *= f.x;
    }

    assert(n == mult);
}

int main() {
	sieve();
	assert(factor[0] == 0);
	assert(factor[1] == 1);

	for (int i = 2; i <= MAX_P; i++) {
		int tmp = i, n = 1;

		while (tmp > 1) {
			n *= factor[tmp];
			tmp /= factor[tmp];
		}

		assert(i == n);
		check(i);
	}
	return 0;
}
