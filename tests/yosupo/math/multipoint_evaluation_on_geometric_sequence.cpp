#include "../../../src/math/polynomial.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, m, a, r;
	cin >> n >> m >> a >> r;

	vector<Zp> c(n);
	each(e, c) cin >> e.x;

	Zp mult = 1;
	each(e, c) {
		e *= mult;
		mult *= a;
	}

	auto ans = chirpz(c, r, m);
	each(p, ans) cout << p.x << ' ';
	cout << '\n';
	return 0;
}
