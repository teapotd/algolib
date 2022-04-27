#include "../../../src/math/berlekamp_massey.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<ll> A(n);
	each(e, A) cin >> e;

	vector<ll> c = massey(A);
	cout << sz(c) << '\n';
	each(e, c) cout << e << ' ';
	cout << '\n';
	return 0;
}
