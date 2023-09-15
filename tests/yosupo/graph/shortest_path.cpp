#include "../../../src/graphs/spfa.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	vector<vector<Edge>> G(n), rev(n);

	rep(i, 0, m) {
		int u, v, c;
		cin >> u >> v >> c;
		G[u].pb({v, c});
		rev[v].pb({u, c});
	}

	vi par;
	auto dist = spfa(G, par, s);

	if (dist[t] == INT64_MAX) {
		cout << "-1\n";
		return 0;
	}

	vi path = {t};
	while (path.back() != s) {
		path.pb(par[path.back()]);
	}

	reverse(all(path));
	cout << dist[t] << ' ' << sz(path)-1 << '\n';
	rep(i, 1, sz(path)) {
		cout << path[i-1] << ' ' << path[i] << '\n';
	}
	return 0;
}
