#include "../../lib/math/montgomery.h"
#include "../testing.h"

int main() {
	ll n, m;
	n = m = rl(1, MOD-1);

	for (int i = 0; i < 100000000; i++) {
		ll mult = rl(1, MOD-1);

		n = (n * mult) % MOD;
		m = redc(m * MG(mult));
		
		// deb(n, m);
		assert(n == m);
	}
	return 0;
}
