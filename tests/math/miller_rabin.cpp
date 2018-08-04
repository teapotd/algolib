#include "../../lib/math/miller_rabin.h"
#include "../../lib/math/sieve.h"
#include "../testing.h"

// Assumes that sieve work

int main() {
  sieve();

  assert(!isPrime(0));
  assert(!isPrime(1));

  rep(p, 2, MAX_P+1) {
    // deb(p, isPrime(p), factor[p]);
    assert(isPrime(p) == (factor[p] == p));
  }

  return 0;
}
