#include "../../../src/math/miller_rabin.h"
#include "../../../src/math/sieve.h"
#include "../testing.h"

// Assumes that sieve work

int main() {
  auto before = now();
  cout << "sieve: " << since(before) << "ms\n";

  assert(!isPrime(0));
  assert(!isPrime(1));

  rep(p, 2, MAX_P+1) {
    // deb(p, isPrime(p), primes[p]);
    assert(isPrime(p) == primes[p]);
  }

  return 0;
}
