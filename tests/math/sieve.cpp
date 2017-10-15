#include "../../lib/math/sieve.h"
#include "../testing.h"

int main() {
	sieve();

	for (int i = 2; i <= MAX_P; i++) {
		int tmp = i, n = 1;
		// printf("%d = ", i);

		while (tmp > 1) {
			n *= primes[tmp];
			// printf("%d ", primes[tmp]);
			tmp /= primes[tmp];
		}
		// printf("\n");

		assert(i == n);
	}
	return 0;
}
