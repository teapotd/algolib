#pragma once
#include "../template.h"

constexpr int MAX_P = 1e6;
bitset<MAX_P+1> primes;
Vi primesList;

// Erathostenes sieve; time: O(n lg lg n)
void sieve() {
	primes.set();
	primes.reset(0);
	primes.reset(1);

	for (int i = 2; i*i <= MAX_P; i++)
		if (primes[i])
			for (int j = i*i; j <= MAX_P; j += i)
				primes.reset(j);

	rep(i, 0, MAX_P+1) if (primes[i])
		primesList.pb(i);
}
