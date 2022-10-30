#include "../../../src/graphs/dominators.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m, s;
	cin >> n >> m >> s;

	vector<vi> G(n);
	rep(i, 0, m) {
		int u, v; cin >> u >> v;
		G[u].pb(v);
	}

	each(d, dominators(G, s)) cout << d << ' ';
	cout << '\n';
	return 0;
}
