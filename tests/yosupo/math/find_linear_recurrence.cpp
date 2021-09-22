#include "../../../src/math/berlekamp_massey.h"

int main() {
	int n; cin >> n;
	vector<ll> A(n);
	each(e, A) cin >> e;

	vector<ll> c = massey(A);
	cout << sz(c) << '\n';
	each(e, c) cout << e << ' ';
	cout << '\n';
	return 0;
}
