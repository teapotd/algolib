#include "../../../src/trees/lca.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	vector<vi> G(n);

	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}

	LCA lca(G, 0);

	while (q--) {
		int u, v, i; cin >> u >> v >> i;
		cout << lca.kthVertex(u, v, i) << '\n';
	}

	return 0;
}
