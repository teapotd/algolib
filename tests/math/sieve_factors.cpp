#include "../../lib/math/sieve_factors.h"
#include "../testing.h"

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
	}
	return 0;
}
