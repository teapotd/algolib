#include "../../../src/math/polynomial.h"

int main() {
	int n; cin >> n;
	vector<pair<Zp, Zp>> points(n);
	each(e, points) cin >> e.x.x;
	each(e, points) cin >> e.y.x;

	auto poly = interpolate(points);
	assert(sz(poly) <= n);
	poly.resize(n);
	each(p, poly) cout << p.x << ' ';
	cout << '\n';
	return 0;
}
