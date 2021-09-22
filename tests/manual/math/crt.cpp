#include "../../../src/math/crt.h"
#include "../testing.h"

ll gcd(ll a, ll b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

ll lcm(ll a, ll b) {
	return a*b / gcd(a, b);
}

int main() {
	ll maxLcm = 0;

	rep(i, 0, 2000000) {
		int d = r(1, 63), e = 63-d;

		ll n = max(ll((1ull<<d)-1) - r(1, 1e6), 1ll);
		ll m = max(ll((1ull<<e)-1) - r(1, 1e6), 1ll);

		ll a = rl(0, n-1);
		ll b = rl(0, m-1);

		Pll ans = crt({a, n}, {b, m});
		ll lc = lcm(n, m);

		if (ans.y == -1) {
			assert(a%lc != b%lc);
			continue;
		}

		assert(ans.y == lc);
		assert(ans.x >= 0 && ans.x < ans.y);
		assert(ans.x%n == a);
		assert(ans.x%m == b);
		maxLcm = max(maxLcm, lc);
	}

	deb(maxLcm);
	return 0;
}
