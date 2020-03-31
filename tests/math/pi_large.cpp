#include "../../src/math/pi_large.h"
#include "../testing.h"

#define MAX_P MAX_P_SEG
#include "../../src/math/sieve_segmented.h"
#undef MAX_P

void bench() {
	initPi();
	std::cout << "initialized pi" << std::endl;

	rep(i, 0, 4) {
		ll k = rl(ll(1e11), ll(2e11));
		ll p = pi(k);
		deb(k, p);
	}
}

int main() {
	// bench();
	// return 0;

	sieve();

	Vi cnt(MAX_P_SEG+1);
	rep(i, 1, MAX_P_SEG+1) {
		cnt[i] = cnt[i-1] + isPrime(i);
	}

	std::cout << "initialized sieve" << std::endl;

	initPi();
	std::cout << "initialized pi" << std::endl;

	while (true) {
		int n = r(1, 1e9);
		ll got = pi(n);
		ll expected = cnt[n];
		deb(n, got, expected);
		if (got != expected) break;
	}

  return 0;
}
