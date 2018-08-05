#pragma once
#include "../template.h"

constexpr int MAX_P = 1e6;
Vi factor(MAX_P+1);

void sieve() {
	for (int i = 2; i*i <= MAX_P; i++)
		if (!factor[i])
			for (int j = i*i; j <= MAX_P; j += i)
				if (!factor[j])
					factor[j] = i;

	rep(i,0,MAX_P+1) if (!factor[i]) factor[i]=i;
}

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
