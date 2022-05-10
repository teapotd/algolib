#include "../../../src/graphs/scc.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	vector<Vi> G(n);

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
	return 0;
}
