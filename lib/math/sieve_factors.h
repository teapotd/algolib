#pragma once
#include "../template.h"

constexpr int MAX_P = 1e6;
Vi factor(MAX_P+1);

// Erathostenes sieve with saving smallest
// factor for each number; time: O(n lg lg n)
void sieve() {
	for (int i = 2; i*i <= MAX_P; i++)
		if (!factor[i])
			for (int j = i*i; j <= MAX_P; j += i)
				if (!factor[j])
					factor[j] = i;

	rep(i,0,MAX_P+1) if (!factor[i]) factor[i]=i;
}

// Factorize n <= MAX_P; time: O(lg n)
// Returns pairs (prime, power), sorted
vector<Pii> factorize(ll n) {
  vector<Pii> ret;
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
