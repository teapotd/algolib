#include "../../../src/math/polynomial.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
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
