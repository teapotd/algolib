#include "../../../src/math/polynomial.h"

int main() {
	int n, m; cin >> n >> m;
	vector<Zp> f(n), g(m);
	each(e, f) cin >> e.x;
	each(e, g) cin >> e.x;

	vector<Zp> q = f/g, r = f%g;

	cout << sz(q) << ' ' << sz(r) << '\n';
	each(e, q) cout << e.x << ' ';
	cout << '\n';
	each(e, r) cout << e.x << ' ';
	cout << '\n';
	return 0;
}
