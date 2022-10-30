#include "../../../src/graphs/general_matching.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<vi> G(n);

	rep(i, 0, m) {
		int u, v; cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}

	vi match;
	cout << blossom(G, match) << '\n';
	rep(i, 0, n) if (match[i] > i) cout << match[i] << ' ' << i << '\n';
	return 0;
}
