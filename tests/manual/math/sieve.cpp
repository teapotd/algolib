#include "../../../src/math/sieve.h"
#include "../../../src/math/miller_rabin.h"
#include "../testing.h"

int main() {
	for (int i = 0; i <= MAX_P; i++) {
		assert(primes[i] == isPrime(i));
	}
	return 0;
}
