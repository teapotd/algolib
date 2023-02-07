#pragma once
#include "../template.h"

constexpr int MAX_P = 1e9;

// Cache-friendly Erathostenes sieve
// ~1.5s on Intel Core i5 for MAX_P = 10^9
// Memory usage: MAX_P/16 bytes
// The bitset stores only odd numbers.
auto primes = [] {
	constexpr int SEG = 1<<18;
	int j, sq = int(sqrt(MAX_P))+1;
	vector<pii> dels;
	bitset<MAX_P/2+1> ret;
	ret.set();
	ret.reset(0);

	for (int i = 3; i <= sq; i += 2) {
		if (ret[i/2]) {
			for (j = i*i; j <= sq; j += i*2)
				ret.reset(j/2);
			dels.pb({ i, j/2 });
		}
	}

	for (int i = sq/2; i <= sz(ret); i += SEG) {
		j = min(i+SEG, sz(ret));
		each(d, dels) for (; d.y < j; d.y += d.x)
			ret.reset(d.y);
	}
	return ret;
}();

bool isPrime(int n) {
	return n == 2 || (n%2 && primes[n/2]);
}
