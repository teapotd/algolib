#include "../../../src/graphs/strongly_connected.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<vi> G(n);

	rep(i, 0, m) {
		int u, v; cin >> u >> v;
		G[u].pb(v);
	}

	SCC scc(G);
	cout << sz(scc.comps) << '\n';

	for (int i = sz(scc.comps)-1; i >= 0; i--) {
		auto& vec = scc.comps[i];
		cout << sz(vec) << ' ';
		each(v, vec) cout << v << ' ';
		cout << '\n';
	}

	// Additional validation.
	vector<bool> seen(n);
	rep(c, 0, sz(scc.comps)) {
		each(v, scc.comps[c]) {
			assert(scc[v] == c);
			assert(!seen[v]);
			seen[v] = true;
		}
	}
	assert(count(all(seen), false) == 0);

	return 0;
}
