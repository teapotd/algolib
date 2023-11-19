#include "../../../src/math/crt.h"
#include "../base_test.hpp"

void deterministic() {
}

void fuzz() {
	rep(i, 0, 2'000'000) {
		int d = 1 + i%63, e = 63-d;
		ll n = max(ll((1ull<<d)-1) - randInt(1, 1e6), 1ll);
		ll m = max(ll((1ull<<e)-1) - randInt(1, 1e6), 1ll);

		ll a = randLong(0, n-1);
		ll b = randLong(0, m-1);

		pll got = crt({a, n}, {b, m});
		ll lc = lcm(n, m);

		if (got.y == -1) {
			assert(a%lc != b%lc);
			assert(got.x == -1);
		} else {
			assert(got.y == lc);
			assert(got.x >= 0 && got.x < got.y);
			assert(got.x%n == a);
			assert(got.x%m == b);
		}
	}
}

void benchmark() {
}
