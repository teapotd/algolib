#include "../../../src/graphs/kth_shortest.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m, s, t, k;
	cin >> n >> m >> s >> t >> k;
	vector<vector<Eppstein::Edge>> G(n);

	rep(i, 0, m) {
		int u, v, c;
		cin >> u >> v >> c;
		G[u].pb({v, c});
	}

	Eppstein paths(G, s, t);
	rep(i, 0, k) cout << paths.nextPath() << '\n';
	return 0;
}
