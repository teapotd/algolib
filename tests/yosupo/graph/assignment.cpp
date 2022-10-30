#include "../../../src/graphs/weighted_matching.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<vector<ll>> mat(n, vector<ll>(n));
	each(row, mat) each(e, row) cin >> e;

	vi L, R;
	cout << hungarian(mat, L, R) << '\n';
	each(v, L) cout << v << ' ';
	cout << '\n';
	return 0;
}
