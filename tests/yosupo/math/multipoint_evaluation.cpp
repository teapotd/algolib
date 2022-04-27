#include "../../../src/math/polynomial.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<Zp> c(n), p(m);
	each(e, c) cin >> e.x;
	each(e, p) cin >> e.x;

	each(e, eval(c, p)) cout << e.x << ' ';
	cout << '\n';
	return 0;
}
