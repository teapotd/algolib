#include "../../../src/graphs/biconnected.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vi> G(n);

	rep(i, 0, m) {
		int u, v;
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}

	Biconnected bi(G);
	auto ans = bi.verts;

	rep(v, 0, n) {
		if (bi[v].empty()) {
			ans.pb({v});
		}
	}

	cout << sz(ans) << '\n';

	each(vec, ans) {
		cout << sz(vec) << ' ';
		each(v, vec) cout << v << ' ';
		cout << '\n';
	}

	return 0;
}
