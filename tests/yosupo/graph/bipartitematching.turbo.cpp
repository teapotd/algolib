#include "../../../src/graphs/turbo_matching.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int l, r, m;
	cin >> l >> r >> m;

	vector<Vi> G(l+r);

	rep(i, 0, m) {
		int a, b; cin >> a >> b;
		G[a].pb(b+l);
		G[b+l].pb(a);
	}

	Vi match;
	int ans = matching(G, match);

	cout << ans << '\n';

	rep(v, 0, l) {
		if (v < match[v]) {
			cout << v << ' ' << match[v]-l << '\n';
		}
	}
	return 0;
}