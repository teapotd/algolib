#include "../../../src/math/phi_prefix_sum.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	ll n; cin >> n;
	calcPhiSum();
	cout << getPhiSum(n+1) << '\n';
	return 0;
}
