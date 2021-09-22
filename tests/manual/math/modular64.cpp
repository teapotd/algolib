#include "../../../src/math/modular64.h"
#include "../testing.h"

constexpr ll MOD = 12345678912345678;

ll naiveMult(__int128 a, __int128 b) {
  return ll(a*b % __int128(MOD));
}

ll naivePow(__int128 a, __int128 p) {
  __int128 ret = 1;
  for (int i = 0; i < p; i++) {
    ret = (ret*a) % __int128(MOD);
  }
  return ll(ret);
}

void check() {
  rep(i, 0, 100000) {
    ll a = rl(0, MOD);
    ll b = rl(0, MOD);
    assert(naiveMult(a, b) == modMul(a, b, MOD));

    rep(p, 0, 10) {
      assert(naivePow(a, p) == modPow(a, p, MOD));
    }
  }
}

void benchMulMod32() {
  auto start = now();

  constexpr ll p = 1e9+7;
  ll a = 1337;

  rep(i, 0, int(1e8)) {
    a = a*(i+1) % p;
  }

  cout << "integer modulo " << since(start) << "ms (" << a << ")" << endl;
}

void benchMulMod64() {
  auto start = now();

  ll a = 1337;

  rep(i, 0, int(1e8)) {
    a = modMul(a, i+1, MOD);
  }

  cout << "long modulo " << since(start) << "ms (" << a << ")" << endl;
}

int main() {
  check();
  benchMulMod32();
  benchMulMod64();
  return 0;
}
