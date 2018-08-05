#pragma once
#include "../template.h"

constexpr int MAX_P = 1e9;
constexpr int SEG_SIZE = 1<<18;
const int MAX_P_SQRT = int(sqrt(MAX_P)+0.5);

bitset<MAX_P/2+1> primes;

bool isPrime(int x) {
  return x == 2 || (x%2 && primes[x/2]);
}

void sieve() {
  vector<Pii> dels;
  primes.set();
  primes.reset(0);

  for (int i = 3; i <= MAX_P_SQRT; i += 2) {
    if (primes[i/2]) {
      int j;
      for (j = i*i; j <= MAX_P_SQRT; j += i*2)
        primes.reset(j/2);
      dels.pb({ i, j/2 });
    }
  }

  for (int seg = MAX_P_SQRT/2;
       seg <= sz(primes); seg += SEG_SIZE) {
    int lim = min(seg+SEG_SIZE, sz(primes));
    each(d, dels) for (;d.y < lim; d.y += d.x)
      primes.reset(d.y);
  }
}
