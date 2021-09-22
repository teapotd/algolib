#include "../../../src/math/polynomial.h"

int main() {
	int n, m; cin >> n >> m;
	vector<Zp> c(n), p(m);
	each(e, c) cin >> e.x;
	each(e, p) cin >> e.x;

	each(e, eval(c, p)) cout << e.x << ' ';
	cout << '\n';
	return 0;
}
