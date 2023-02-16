#include "../../../src/geo2d/rmst.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<vec> points(n);
	each(p, points) cin >> p.x >> p.y;

	vector<pair<ll, pii>> edges;
	ll ans = rmst(points, edges);

	cout << ans << '\n';
	each(e, edges) {
		cout << e.y.x << ' ' << e.y.y << '\n';
	}
	return 0;
}
