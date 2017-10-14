#include "../../lib/math/montgomery.h"
#include "../testing.h"

constexpr ll MOD = 1e9+9;

int main() {
	ll mgInv = getMgInv(MOD);

	ll n, m;
	n = m = r(1, MOD-1);

	while (true) {
		ll mult = r(1, MOD-1);

		n = (n * mult) % MOD;
		m = redc(m * mgShift(mult, MOD), MOD, mgInv);
		
		// printf("%lld %lld\n", n, m);
		assert(n == m);
	}

	return 0;
}
