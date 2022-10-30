#include "../../../src/geometry/rmst.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<pii> points(n);
	each(p, points) cin >> p.x >> p.y;

	vector<vector<pii>> G;
	ll ans = rmst(points, G);

	cout << ans << '\n';

	rep(i, 0, sz(G)) {
		each(e, G[i]) {
			if (i < e.x) {
				cout << i << ' ' << e.x << '\n';
			}
		}
	}
	return 0;
}
