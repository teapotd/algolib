#include "../../lib/math/pollard_rho.h"
#include "../testing.h"

constexpr ll MAX_N = ll(MAX_P)*MAX_P*MAX_P;

void check(ll n) {
    auto factors = factorize(n);
    ll mult = 1;
    // deb(n, factors);

    rep(i, 0, sz(factors)) {
      auto f = factors[i];

      if (i > 0) assert(factors[i-1].x < f.x);
      assert(isPrime(f.x));
      rep(j, 0, f.y) mult *= f.x;
    }

    assert(n == mult);
}

int main() {
  sieve();

  rep(n, 1, 100) check(n);
  rep(k, 0, 1000) check(rl(1, MAX_N));
  return 0;
}
