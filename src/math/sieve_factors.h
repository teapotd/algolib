#pragma once
#include "../template.h"

constexpr int MAX_P = 1e6;

// Erathostenes sieve that saves smallest
// factor for each number; time: O(n lg lg n)
vi factor = [] {
	vi f(MAX_P+1);
	iota(all(f), 0);
	for (int i = 2; i*i <= MAX_P; i++)
		if (f[i] == i)
			for (int j = i*i; j <= MAX_P; j += i)
				f[j] = min(f[j], i);
	return f;
}();

// Factorize n <= MAX_P; time: O(lg n)
// Returns pairs (prime, power), sorted
vector<pii> factorize(ll n) {
	vector<pii> ret;
	while (n > 1) {
		int f = factor[n];
		if (ret.empty() || ret.back().x != f)
			ret.pb({ f, 1 });
		else
			ret.back().y++;
		n /= f;
	}
	return ret;
}
