#include "../../../src/math/polynomial.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<Zp> f(n);
	each(e, f) cin >> e.x;

	vector<Zp> g = log(f, n);
	each(e, g) cout << e.x << ' ';
	cout << '\n';
	return 0;
}
