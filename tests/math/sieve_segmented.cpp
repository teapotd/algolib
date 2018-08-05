#include "../../lib/math/sieve.h"
#define sieve sieve2
#define primes primes2
#define MAX_P MAX_P2
#include "../../lib/math/sieve_segmented.h"
#undef sieve
#undef primes
#undef MAX_P
#include "../testing.h"

int main() {
  sieve2();
  // cout << "1\n";
  // sieve();
  // cout << "2\n";

  // rep(i, 0, MAX_P+1) {
  //   assert(isPrime(i) == primes[i]);
  // }
  return 0;
}
