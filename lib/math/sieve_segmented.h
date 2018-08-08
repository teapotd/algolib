#pragma once
#include "../template.h"

constexpr int MAX_P = 1e9;
bitset<MAX_P/2+1> primes; // Only odd numbers

// Cache-friendly Erathostenes sieve
// ~1.5s on Intel Core i5 for MAX_P = 10^9
// Memory usage: MAX_P/16 bytes
void sieve() {
	constexpr int SEG_SIZE = 1<<18;
	int pSqrt = int(sqrt(MAX_P)+0.5);
	vector<Pii> dels;
	primes.set();
	primes.reset(0);

	for (int i = 3; i <= pSqrt; i += 2) {
		if (primes[i/2]) {
			int j;
			for (j = i*i; j <= pSqrt; j += i*2)
				primes.reset(j/2);
			dels.pb({ i, j/2 });
		}
	}

	for (int seg = pSqrt/2;
			 seg <= sz(primes); seg += SEG_SIZE) {
		int lim = min(seg+SEG_SIZE, sz(primes));
		each(d, dels) for (;d.y < lim; d.y += d.x)
			primes.reset(d.y);
	}
}

bool isPrime(int x) {
	return x == 2 || (x%2 && primes[x/2]);
}
