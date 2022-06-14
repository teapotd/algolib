#include "../../../src/math/subset_sum.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, t; cin >> n >> t;
	Poly counts(t+1);

	rep(i, 0, n) {
		int k; cin >> k;
		counts[k] += 1;
	}

	Poly ans = subsetSum(counts, t+1);
	rep(i, 1, t+1) cout << ans[i].x << ' ';
	cout << '\n';
	return 0;
}
