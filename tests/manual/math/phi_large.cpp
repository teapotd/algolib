#include "../../../src/math/phi_large.h"
#define phi phi2
#include "../../../src/math/phi_precompute.h"
#undef phi
#include "../testing.h"

int main() {
  sieve();
  calcPhi();
  rep(i, 1, MAX_PHI+1) {
    deb(i, phi(i));
    assert(phi2[i] == phi(i));
  }
  return 0;
}
