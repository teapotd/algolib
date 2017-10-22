#pragma once
#include "../template.h"

// Calculate smallest prime factors for all numbers in [0;MAX_P]
// Time complexity: O(n lg lg n)

constexpr int MAX_P = 1000000;

vector<int> primes(MAX_P+1);

void sieve() {
	primes[0] = 0;
	primes[1] = 1;

	for (int i = 2; i*i <= MAX_P; i++) {
		if (primes[i]) continue;
		for (int j = i*i; j <= MAX_P; j += i) if (!primes[j]) primes[j] = i;
	}

	rep(i, 2, MAX_P+1) if (!primes[i]) primes[i] = i;
}
