#include "../../../src/graphs/general_matching_w.h"

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	WeightedBlossom G(n);

	rep(i, 0, m) {
		int u, v, w;
		cin >> u >> v >> w;
		G.addEdge(u, v, w);
	}

	int matchSize;
	ll weight;
	Vi match = G.solve(matchSize, weight);

	cout << matchSize << ' ' << weight << '\n';
	rep(i, 0, n) if (match[i] > i) cout << i << ' ' << match[i] << '\n';
	return 0;
}
