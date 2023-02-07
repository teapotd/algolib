#include "../../../src/math/sieve_segmented.h"
#define isPrime isPrimeMillerRabin
#include "../../../src/math/miller_rabin.h"
#undef isPrime
#include "../testing.h"

int main() {
	for (int i = 0; i <= int(5e6); i++) {
		assert(isPrime(i) == isPrimeMillerRabin(i));
		assert(isPrime(MAX_P-i) == isPrimeMillerRabin(MAX_P-i));
	}
	return 0;
}
