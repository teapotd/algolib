#include "../../../src/math/phi_prefix_sum.h"
#include "../testing.h"

vi naivePhi(1e8+1);
vector<ll> naivePhiSum;

void calcPhiNaive() {
	iota(all(naivePhi), 0);
	rep(i, 2, sz(naivePhi)) if (naivePhi[i] == i)
		for (int j = i; j < sz(naivePhi); j += i)
			naivePhi[j] = naivePhi[j] / i * (i-1);

	naivePhiSum.resize(sz(naivePhi)+1);

	rep(i, 0, sz(naivePhi)) {
		naivePhiSum[i+1] = (naivePhiSum[i] + naivePhi[i]) % MOD;
	}
}

void check(int n) {
	ll expected = naivePhiSum[n];
	ll got = getPhiSum(n);
	deb(expected, got);
}

int main() {
  calcPhiNaive();
  cout << "naive computed\n";

  check(123);
  check(1234567);
  check(1e7+5);
  check(89123123);

  deb(getPhiSum(1987654321));
  deb(getPhiSum(1987654321));
  return 0;
}
