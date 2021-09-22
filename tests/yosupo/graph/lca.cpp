#include "../../../src/trees/lca_linear.h"

int main() {
	int n, q;
	cin >> n >> q;

	vector<Vi> G(n);
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
