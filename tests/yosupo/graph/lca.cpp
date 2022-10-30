#include "../../../src/trees/lca.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, q;
	cin >> n >> q;

	vector<vi> G(n);
	rep(i, 1, n) {
		int p; cin >> p;
		G[i].pb(p);
		G[p].pb(i);
	}

	LCA lca(G, 0);
	while (q--) {
		int u, v; cin >> u >> v;
		cout << lca(u, v) << '\n';
	}
	return 0;
}
