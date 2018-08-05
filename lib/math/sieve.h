#pragma once
#include "../template.h"

constexpr int MAX_P = 1e6;
bitset<MAX_P+1> primes;

void sieve() {
  primes.set();
  primes.reset(0);
  primes.reset(1);

  for (int i = 2; i*i <= MAX_P; i++)
    if (primes[i])
      for (int j = i*i; j <= MAX_P; j += i)
        primes.reset(j);
}
