#pragma once
#include "../template.h"
#include "modular64.h"

// Miller-Rabin primality test
// time O(k*lg^2 n), where k = number of bases

// Deterministic for p <= 10^9
// constexpr ll BASES[] = {
//   336781006125, 9639812373923155
// };

// Deterministic for p <= 2^64
constexpr ll BASES[] = {
  2,325,9375,28178,450775,9780504,1795265022
};

bool isPrime(ll p) {
  if (p == 2) return true;
  if (p <= 1 || p%2 == 0) return false;

  ll d = p-1, times = 0;
  while (d%2 == 0) d /= 2, times++;

  each(a, BASES) if (a%p) {
    // ll a = rand() % (p-1) + 1;
    ll b = modPow(a%p, d, p);
    if (b == 1 || b == p-1) continue;

    rep(i, 1, times) {
      b = modMul(b, b, p);
      if (b == p-1) break;
    }

    if (b != p-1) return false;
  }

  return true;
}
