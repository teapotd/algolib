#include "../../../src/graphs/dominators.h"

int main() {
	int n, m, s;
	cin >> n >> m >> s;

	vector<Vi> G(n);
	rep(i, 0, m) {
		int u, v; cin >> u >> v;
		G[u].pb(v);
	}

	each(d, dominators(G, s)) cout << d << ' ';
	cout << '\n';
	return 0;
}
